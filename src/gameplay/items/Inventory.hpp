#pragma once
#include "gameplay/items/Item.hpp"
#include <vector>
#include <optional>
#include <unordered_map>

class Inventory {
public:
    explicit Inventory(int slotCount = 40);

    int getSlotCount() const { return m_slotCount; }
    void setCarryCapacity(float maxWeight) { m_carryCapacity = maxWeight; }
    float getCarryCapacity() const { return m_carryCapacity; }

    bool addItem(const Item& item);
    bool removeItem(const std::string& itemId, int count = 1);
    bool hasItem(const std::string& itemId, int count = 1) const;
    int getItemCount(const std::string& itemId) const;

    const std::vector<std::optional<Item>>& getSlots() const { return m_slots; }
    std::optional<Item> getSlot(int index) const;

    bool equipItem(EquipSlot slot, int inventorySlotIndex);
    bool unequipItem(EquipSlot slot);
    const Item* getEquipped(EquipSlot slot) const;

    float getTotalWeight() const;
    bool isEncumbered() const;

private:
    int m_slotCount{40};
    float m_carryCapacity{50.0f};
    std::vector<std::optional<Item>> m_slots;
    std::unordered_map<EquipSlot, Item> m_equipped;
};
