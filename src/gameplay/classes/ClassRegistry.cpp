#include "gameplay/classes/ClassRegistry.hpp"
#include <stdexcept>

ClassRegistry::ClassRegistry() {
    registerClasses();
}

void ClassRegistry::registerClasses() {
    m_classes[ClassType::Juggernaut] = ClassDefinition{
        ClassType::Juggernaut,
        "Juggernaut",
        "Immovable heavy armor anchor, fortress shield protector, and seismic hammer devatator.",
        Attributes{16, 8, 8, 14, 10, 10},
        "Greatsword",
        "Kinetic Impact Siphon Core",
        "Kinetic Charge"
    };

    m_classes[ClassType::Berserker] = ClassDefinition{
        ClassType::Berserker,
        "Berserker",
        "Savage dual-wielding brawler thriving on missing health, lifesteal, and unstoppable rage.",
        Attributes{15, 12, 6, 12, 8, 8},
        "Greataxe",
        "Adrenal Hyper-Surge Pump",
        "Rage"
    };

    m_classes[ClassType::Gunslinger] = ClassDefinition{
        ClassType::Gunslinger,
        "Gunslinger",
        "Master of firearms, weakpoint marksmanship, specialized munitions, and trick-shot ballistics.",
        Attributes{10, 16, 10, 10, 8, 12},
        "Revolver",
        "Ocular Ballistic Telemetry Scope",
        "Focus"
    };

    m_classes[ClassType::Phantom] = ClassDefinition{
        ClassType::Phantom,
        "Phantom",
        "Shadow assassin weaving through physical barriers, executing backstabs, and applying neurotoxins.",
        Attributes{8, 16, 10, 8, 8, 12},
        "Dagger",
        "Phase-Shift Cloaking Shroud",
        "Shadow Shroud"
    };

    m_classes[ClassType::Technomancer] = ClassDefinition{
        ClassType::Technomancer,
        "Technomancer",
        "Cyber-mage bridging arc electromancy, kinetic forcefields, autonomous drones, and nanites.",
        Attributes{6, 10, 16, 8, 10, 14},
        "Wand",
        "Subdermal Tesla Coil Conduit",
        "Overcharge"
    };

    m_classes[ClassType::Medic] = ClassDefinition{
        ClassType::Medic,
        "Medic",
        "Combat surgeon wielding radiant healing frequencies, biological hazards, and cellular stims.",
        Attributes{8, 10, 12, 12, 14, 12},
        "Scepter",
        "Nanite Auto-Triage Defibrillator",
        "Bio-Triage Stock"
    };

    m_classes[ClassType::Symbiote] = ClassDefinition{
        ClassType::Symbiote,
        "Symbiote",
        "Shapeshifter bonded with an alien parasite, lashing tendrils, infesting hosts, and commanding spores.",
        Attributes{12, 12, 8, 14, 12, 8},
        "Tendril Whip",
        "Primal Bio-Metamorphic Tendril Harness",
        "Biomass"
    };

    m_classes[ClassType::Warden] = ClassDefinition{
        ClassType::Warden,
        "Warden",
        "Inviolable holy paladin, wielding sacred warhammers, protective auras, and divine oaths.",
        Attributes{14, 8, 10, 12, 14, 8},
        "Warhammer",
        "Luminous Bastion Hard-Light Aegis",
        "Holy Fervor"
    };

    m_classes[ClassType::Reanimator] = ClassDefinition{
        ClassType::Reanimator,
        "Reanimator",
        "Necromancer harvesting souls, raising skeleton legions, forging bone armor, and detonating corpses.",
        Attributes{6, 8, 16, 10, 12, 10},
        "Bone Scythe",
        "Ossified Soul-Cage Carapace",
        "Soul Shards"
    };

    m_classList.clear();
    for (const auto& [type, def] : m_classes) {
        m_classList.push_back(def);
    }
}

const ClassDefinition& ClassRegistry::getClass(ClassType type) const {
    auto it = m_classes.find(type);
    if (it != m_classes.end()) {
        return it->second;
    }
    throw std::runtime_error("Class type not found in registry");
}
