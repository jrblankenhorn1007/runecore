#include "gameplay/items/Inventory.hpp"
#include <algorithm>

Inventory::Inventory(int slotCount) : m_slotCount(slotCount) {
    m_slots.resize(m_slotCount, std::nullopt);
}

bool Inventory::addItem(const Item& item) {
    Item toAdd = item;

    // First try stacking if stackable
    if (toAdd.stackable) {
        for (auto& slot : m_slots) {
            if (slot.has_value() && slot->id == toAdd.id) {
                int space = slot->maxStack - slot->quantity;
                if (space > 0) {
                    int addAmount = std::min(space, toAdd.quantity);
                    slot->quantity += addAmount;
                    toAdd.quantity -= addAmount;
                    if (toAdd.quantity <= 0) {
                        return true;
                    }
                }
            }
        }
    }

    // Place remaining into empty slot
    for (auto& slot : m_slots) {
        if (!slot.has_value()) {
            slot = toAdd;
            return true;
        }
    }

    return false; // Inventory full
}

bool Inventory::removeItem(const std::string& itemId, int count) {
    if (!hasItem(itemId, count)) return false;

    int remainingToRemove = count;
    for (auto& slot : m_slots) {
        if (slot.has_value() && slot->id == itemId) {
            if (slot->quantity <= remainingToRemove) {
                remainingToRemove -= slot->quantity;
                slot = std::nullopt;
            } else {
                slot->quantity -= remainingToRemove;
                remainingToRemove = 0;
            }
            if (remainingToRemove <= 0) break;
        }
    }

    return true;
}

bool Inventory::hasItem(const std::string& itemId, int count) const {
    return getItemCount(itemId) >= count;
}

int Inventory::getItemCount(const std::string& itemId) const {
    int total = 0;
    for (const auto& slot : m_slots) {
        if (slot.has_value() && slot->id == itemId) {
            total += slot->quantity;
        }
    }
    return total;
}

std::optional<Item> Inventory::getSlot(int index) const {
    if (index >= 0 && index < m_slotCount) {
        return m_slots[index];
    }
    return std::nullopt;
}

bool Inventory::equipItem(EquipSlot slot, int inventorySlotIndex) {
    if (inventorySlotIndex < 0 || inventorySlotIndex >= m_slotCount) return false;
    if (!m_slots[inventorySlotIndex].has_value()) return false;

    Item toEquip = m_slots[inventorySlotIndex].value();
    if (toEquip.equipSlot != slot) return false;

    // Remove from inventory
    m_slots[inventorySlotIndex] = std::nullopt;

    // If slot already occupied, swap back
    auto it = m_equipped.find(slot);
    if (it != m_equipped.end()) {
        m_slots[inventorySlotIndex] = it->second;
    }

    m_equipped[slot] = toEquip;
    return true;
}

bool Inventory::unequipItem(EquipSlot slot) {
    auto it = m_equipped.find(slot);
    if (it == m_equipped.end()) return false;

    Item unequipped = it->second;
    // Try to add back to inventory
    if (addItem(unequipped)) {
        m_equipped.erase(it);
        return true;
    }

    return false; // Inventory was full
}

const Item* Inventory::getEquipped(EquipSlot slot) const {
    auto it = m_equipped.find(slot);
    if (it != m_equipped.end()) {
        return &it->second;
    }
    return nullptr;
}

float Inventory::getTotalWeight() const {
    float total = 0.0f;
    for (const auto& slot : m_slots) {
        if (slot.has_value()) {
            total += slot->weight * slot->quantity;
        }
    }
    for (const auto& [slot, item] : m_equipped) {
        total += item.weight * item.quantity;
    }
    return total;
}

bool Inventory::isEncumbered() const {
    return getTotalWeight() > m_carryCapacity;
}
