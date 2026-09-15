#!/usr/bin/env python3
"""Normalize item and enemy documentation into category/entity dossiers."""

from pathlib import Path
import re
import os
from typing import Optional

ROOT = Path(__file__).resolve().parents[1]
ITEMS = ROOT / "docs" / "items"
ENEMIES = ROOT / "docs" / "enemies"


def slugify(value: str) -> str:
    value = re.sub(r"[*`$]", "", value).strip().lower()
    value = value.replace("&", "and")
    value = re.sub(r"[^a-z0-9]+", "-", value)
    return value.strip("-") or "entity"


def clean(value: str) -> str:
    return re.sub(r"[*`]", "", value).strip()


def source_rows(path: Path):
    header = None
    rows = []
    for line in path.read_text().splitlines():
        if not line.startswith("|"):
            continue
        cells = [cell.strip() for cell in line.strip().strip("|").split("|")]
        if not cells or all(set(cell) <= {"-", ":", " "} for cell in cells):
            continue
        if header is None and any(cell.lower().strip() in {"id", "name", "weapon", "item", "armor", "item name", "part name", "material name", "tool name", "accessory name", "consumable name"} for cell in cells):
            header = cells
            continue
        if header is None:
            continue
        if len(cells) == len(header):
            rows.append(dict(zip(header, cells)))
    return rows


def row_value(row, *names):
    lowered = {key.lower().strip(): value for key, value in row.items()}
    for name in names:
        if name.lower() in lowered:
            return lowered[name.lower()]
    return "Not specified"


def stable_id(row):
    value = row_value(row, "id", "weapon id", "armor id", "item id")
    match = re.search(r"`([^`]+)`", value)
    return match.group(1) if match else clean(value)


def entity_name(row):
    return clean(row_value(row, "name", "weapon", "item", "armor", "item name", "part name", "material name", "tool name", "accessory name", "consumable name"))


def implemented_status(entity_id: str):
    if not entity_id or entity_id == "Not specified":
        return "No", "Not mapped to runtime code"
    for source in (ROOT / "src", ROOT / "tests"):
        for path in source.rglob("*"):
            if path.is_file() and path.suffix in {".cpp", ".hpp", ".h", ".json"}:
                if entity_id in path.read_text(errors="ignore"):
                    return "Yes", str(path.relative_to(ROOT))
    return "No", "Not mapped to runtime code"


def asset_fields(name: str, kind: str):
    if kind == "enemy" and "slime" in name.lower():
        asset = "assets/generated/staging/enemy_slime_01.png"
        if (ROOT / asset).exists():
            return "Yes", asset
    return "No", "No generated asset"


def dossier_text(row, source: Path, category: str, kind: str, destination: Optional[Path] = None) -> str:
    name = entity_name(row)
    entity_id = stable_id(row)
    implemented, implementation = implemented_status(entity_id)
    generated, asset = asset_fields(name, kind)
    entity_type = "Weapon" if kind == "weapon" else "Enemy" if kind == "enemy" else "Item"
    stats = "\n".join(f"| {key.strip()} | {value.strip()} |" for key, value in row.items())
    source_link = f"../{source.name}" if destination is None else os.path.relpath(source, destination.parent)
    return f"""# {name}\n\n**Stable ID:** `{entity_id}`  \n**Entity type:** {entity_type}  \n**Category:** {category}  \n**Implemented:** {implemented}  \n**Implementation:** `{implementation}`  \n**Asset generated:** {generated}  \n**Asset:** {asset}  \n**Source catalog:** [{source.name}]({source_link})\n\n## Catalog Data\n\n| Field | Value |\n|---|---|\n{stats}\n\n"""


def ensure_metadata(path: Path, kind: str):
    text = path.read_text()
    if "**Asset generated:**" in text:
        return
    lines = text.splitlines()
    if not lines or not lines[0].startswith("# "):
        return
    name = clean(lines[0][2:])
    id_match = re.search(r"\*\*(?:Weapon )?ID:\*\*\s*`?([^`\s]+)", text, re.I)
    entity_id = id_match.group(1) if id_match else "Not specified"
    implemented, implementation = implemented_status(entity_id)
    generated, asset = asset_fields(name, kind)
    block = [
        f"**Implemented:** {implemented}  ",
        f"**Implementation:** `{implementation}`  ",
        f"**Asset generated:** {generated}  ",
        f"**Asset:** {asset}  ",
    ]
    insert_at = 1
    while insert_at < len(lines) and (lines[insert_at].startswith("**") or not lines[insert_at].strip()):
        insert_at += 1
    lines[insert_at:insert_at] = [""] + block + [""]
    path.write_text("\n".join(lines) + "\n")


def migrate_catalogs():
    category_roots = [ITEMS / name for name in ("armor", "accessories", "consumables", "materials", "tools")]
    for category_root in category_roots:
        for catalog in sorted(category_root.glob("*.md")):
            if catalog.name.endswith("_index.md") or catalog.name in {"items_overview.md", "README.md"}:
                continue
            if "This is a navigation index." in catalog.read_text():
                continue
            kind = "item"
            rows = source_rows(catalog)
            if not rows:
                continue
            category = catalog.parent.name.replace("_", " ").title()
            dossier_dir = catalog.parent / slugify(catalog.stem)
            dossier_dir.mkdir(exist_ok=True)
            links = []
            for row in rows:
                name = entity_name(row)
                if not name or name.lower() in {"name", "weapon", "item"}:
                    continue
                target = dossier_dir / f"{slugify(name)}.md"
                if not target.exists():
                    target.write_text(dossier_text(row, catalog, category, kind))
                else:
                    ensure_metadata(target, kind)
                links.append(f"- [{name}]({dossier_dir.name}/{target.name})")
            catalog.write_text(
                f"# {catalog.stem.replace('_', ' ').title()} Index\n\n"
                f"This is a navigation index. Each entity has its own Markdown dossier in `{dossier_dir.name}/`.\n\n"
                "## Entities\n\n" + "\n".join(links) + "\n"
            )


def migrate_weapon_catalogs():
    weapon_root = ITEMS / "weapons"
    category_by_catalog = {
        "daggers_knives.md": "melee", "swords_greatswords.md": "melee", "heavy_axes_hammers_spears.md": "melee",
        "revolvers_pistols.md": "ballistic", "rifles_carbines.md": "ballistic", "heavy_firearms_snipers.md": "ballistic", "shotguns.md": "ballistic",
        "plasma_blasters.md": "energy", "energy_weapons.md": "energy",
        "staffs_scepters_grimoires.md": "magic", "wands_scepters.md": "magic", "shields_deflectors.md": "shields",
    }
    for catalog_name, category in category_by_catalog.items():
        catalog = weapon_root / catalog_name
        rows = source_rows(catalog)
        links = []
        category_dir = weapon_root / category
        category_dir.mkdir(exist_ok=True)
        for row in rows:
            name = entity_name(row)
            if name == "Not specified" or name.lower() in {"name", "weapon", "item", "armor", "weapon name", "item name"}:
                continue
            target = category_dir / f"{slugify(name)}.md"
            target.write_text(dossier_text(row, catalog, category.title(), "weapon", target))
            links.append(f"- [{name}](./{category}/{target.name})")
        catalog.write_text(f"# {catalog.stem.replace('_', ' ').title()} Index\n\nThis family is organized in the canonical weapon category folder. Each weapon has one Markdown dossier.\n\n" + "\n".join(links) + "\n")


def normalize_existing():
    for path in ITEMS.rglob("*.md"):
        if any(part in {"melee", "ballistic", "energy", "magic", "shields"} for part in path.parts):
            ensure_metadata(path, "weapon")
    for path in ENEMIES.rglob("*.md"):
        ensure_metadata(path, "enemy")


def organize_armor_types():
    armor_root = ITEMS / "armor"
    for source in sorted(armor_root.iterdir()):
        if not source.is_dir() or source.name in {"light", "medium", "heavy", "robes", "tech", "chitin", "holy", "utility", "untyped"}:
            continue
        for dossier in source.glob("*.md"):
            text = dossier.read_text()
            match = re.search(r"\| Type \| ([^|]+) \|", text, re.I)
            armor_type = slugify(match.group(1)) if match else "untyped"
            destination = armor_root / armor_type
            destination.mkdir(exist_ok=True)
            target = destination / dossier.name
            if not target.exists():
                dossier.rename(target)
        try:
            source.rmdir()
        except OSError:
            pass


def normalize_weapon_indexes():
    weapon_root = ITEMS / "weapons"
    category_by_catalog = {
        "daggers_knives.md": "melee",
        "swords_greatswords.md": "melee",
        "heavy_axes_hammers_spears.md": "melee",
        "revolvers_pistols.md": "ballistic",
        "rifles_carbines.md": "ballistic",
        "heavy_firearms_snipers.md": "ballistic",
        "shotguns.md": "ballistic",
        "plasma_blasters.md": "energy",
        "energy_weapons.md": "energy",
        "staffs_scepters_grimoires.md": "magic",
        "wands_scepters.md": "magic",
        "shields_deflectors.md": "shields",
    }
    for catalog_name, category in category_by_catalog.items():
        catalog = weapon_root / catalog_name
        catalog.write_text(
            f"# {catalog.stem.replace('_', ' ').title()} Index\n\n"
            "This family is organized in the canonical weapon category folder. "
            "Each weapon has one Markdown dossier.\n\n"
            f"- [Open the {category} weapon category](./{category}/)\n"
        )


def normalize_armor_entity_types():
    for dossier in (ITEMS / "armor").glob("**/*.md"):
        if dossier.name.endswith("_index.md") or dossier.parent.name == "armor":
            continue
        text = dossier.read_text()
        text = text.replace("**Entity type:** Item", "**Entity type:** Armor", 1)
        dossier.write_text(text)


def normalize_armor_indexes():
    armor_root = ITEMS / "armor"
    locations = {dossier.name: dossier.parent.name for dossier in armor_root.glob("*/*.md")}
    for catalog in armor_root.glob("*.md"):
        if catalog.name == "armor_index.md":
            continue
        text = catalog.read_text()
        text = re.sub(
            r"\(([^/]+)/([^)/]+\.md)\)",
            lambda match: f"({locations[match.group(2)]}/{match.group(2)})" if match.group(2) in locations else match.group(0),
            text,
        )
        catalog.write_text(text)


def retire_grouped_catalogs():
    categories = ["armor", "accessories", "consumables", "materials", "tools"]
    for category in categories:
        category_root = ITEMS / category
        index = category_root / f"{category}_index.md"
        if category == "armor":
            index = category_root / "armor_index.md"
        dossier_files = sorted(category_root.glob("*/*.md"))
        links = [f"- [{dossier.stem.replace('-', ' ').title()}]({dossier.parent.name}/{dossier.name})" for dossier in dossier_files]
        if category != "armor":
            index.write_text(
                f"# {category.title()} Index\n\n"
                "Each entity has one Markdown dossier in a category folder.\n\n"
                + "\n".join(links) + "\n"
            )
        for dossier in dossier_files:
            text = dossier.read_text()
            source_link = os.path.relpath(index, dossier.parent)
            text = re.sub(r"\*\*Source catalog:\*\* .*", f"**Source catalog:** [{index.name}]({source_link})", text)
            dossier.write_text(text)
        for catalog in category_root.glob("*.md"):
            if catalog != index:
                catalog.unlink()

    weapon_root = ITEMS / "weapons"
    weapon_index = weapon_root / "weapons_index.md"
    for dossier in weapon_root.glob("*/*.md"):
        text = dossier.read_text()
        source_link = os.path.relpath(weapon_index, dossier.parent)
        text = re.sub(r"\*\*Source catalog:\*\* .*", f"**Source catalog:** [{weapon_index.name}]({source_link})", text)
        dossier.write_text(text)
    for catalog in weapon_root.glob("*.md"):
        if catalog != weapon_index:
            catalog.unlink()


if __name__ == "__main__":
    migrate_weapon_catalogs()
    migrate_catalogs()
    normalize_existing()
    organize_armor_types()
    normalize_weapon_indexes()
    normalize_armor_entity_types()
    normalize_armor_indexes()
    retire_grouped_catalogs()