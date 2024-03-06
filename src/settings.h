#pragma once

#include "util.h"

using namespace RE; 
namespace JunkIt {
    class Settings {
        public:

            enum class SortPriority {
                kWeightHighLow = 0,
                kWeightLowHigh = 1,
                kValueHighLow = 2,
                kValueLowHigh = 3,
                kValueWeightHighLow = 4,
                kValueWeightLowHigh = 5,
                kChaos = 6
            };

            struct JunkTransfer {
                bool ConfirmTransfer = true;
                SortPriority TransferPriority = SortPriority::kChaos;
                BGSListForm* TransferList;
            };

            struct JunkSell {
                bool ConfirmSell = true;
                SortPriority SellPriority = SortPriority::kChaos;
                BGSListForm* SellList;
            };

            struct JunkProtection {
                bool ProtectEquipped = true;
                bool ProtectFavorites = true;
                bool ProtectEnchanted = false;
            };

            static void Load() {
                SKSE::log::info(" ");
                SKSE::log::info("Updating Settings...");

                std::string priorityString = "";
                JunkList = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x804)->As<BGSListForm>();
                UnjunkedList = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x80E)->As<BGSListForm>();
                IsJunkKYWD = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x802)->As<BGSKeyword>();

                MarkJunkKey = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x817)->As<TESGlobal>()->value;
                TransferJunkKey = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x818)->As<TESGlobal>()->value;

                TESGlobal* ConfirmTransfer = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x808)->As<TESGlobal>();
                TESGlobal* TransferPriority = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x80A)->As<TESGlobal>();
                BGSListForm* TransferList = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x80C)->As<BGSListForm>();

                JunkTransfer.ConfirmTransfer = ConfirmTransfer->value != 0;
                JunkTransfer.TransferPriority = static_cast<SortPriority>(TransferPriority->value);
                JunkTransfer.TransferList = TransferList;

                // Translate the SortPriority to a string for log
                switch (JunkTransfer.TransferPriority) {
                    case SortPriority::kWeightHighLow:
                        priorityString = "Weight [High > Low]";
                        break;
                    case SortPriority::kWeightLowHigh:
                        priorityString = "Weight [Low > High]";
                        break;
                    case SortPriority::kValueHighLow:
                        priorityString = "Value [High > Low]";
                        break;
                    case SortPriority::kValueLowHigh:
                        priorityString = "Value [Low > High]";
                        break;
                    case SortPriority::kValueWeightHighLow:
                        priorityString = "Value/Weight [High > Low]";
                        break;
                    case SortPriority::kValueWeightLowHigh:
                        priorityString = "Value/Weight [Low > High]";
                        break;
                    case SortPriority::kChaos:
                        priorityString = "Chaos";
                        break;
                }

                SKSE::log::info(
                    "Transfer Option Settings | ConfirmTransfer: {} | TransferPriority: {}", 
                    JunkTransfer.ConfirmTransfer,
                    priorityString
                );

                TESGlobal* ConfirmSell = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x809)->As<TESGlobal>();
                TESGlobal* SellPriority = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x80B)->As<TESGlobal>();
                BGSListForm* SellList = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x80D)->As<BGSListForm>();

                JunkSell.ConfirmSell = ConfirmSell->value != 0;
                JunkSell.SellPriority = static_cast<SortPriority>(SellPriority->value);
                JunkSell.SellList = SellList;

                // Translate the SortPriority to a string for log
                switch (JunkSell.SellPriority) {
                    case SortPriority::kWeightHighLow:
                        priorityString = "Weight [High > Low]";
                        break;
                    case SortPriority::kWeightLowHigh:
                        priorityString = "Weight [Low > High]";
                        break;
                    case SortPriority::kValueHighLow:
                        priorityString = "Value [High > Low]";
                        break;
                    case SortPriority::kValueLowHigh:
                        priorityString = "Value [Low > High]";
                        break;
                    case SortPriority::kValueWeightHighLow:
                        priorityString = "Value/Weight [High > Low]";
                        break;
                    case SortPriority::kValueWeightLowHigh:
                        priorityString = "Value/Weight [Low > High]";
                        break;
                    case SortPriority::kChaos:
                        priorityString = "Chaos";
                        break;
                }

                SKSE::log::info(
                    "Sell Option Settings | ConfirmSell: {} | SellPriority: {}",
                    JunkSell.ConfirmSell,
                    priorityString
                );

                TESGlobal* ProtectEquipped = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x810)->As<TESGlobal>();
                TESGlobal* ProtectFavorites = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x811)->As<TESGlobal>();
                TESGlobal* ProtectEnchanted = FormUtil::Form::GetFormFromMod("JunkIt.esp", 0x813)->As<TESGlobal>();

                JunkProtection.ProtectEquipped = ProtectEquipped->value != 0;
                JunkProtection.ProtectFavorites = ProtectFavorites->value != 0;
                JunkProtection.ProtectEnchanted = ProtectEnchanted->value != 0;

                SKSE::log::info(
                    "Protection Settings | ProtectEquipped: {} | ProtectFavorites: {} | ProtectEnchanted: {}",
                    JunkProtection.ProtectEquipped,
                    JunkProtection.ProtectFavorites,
                    JunkProtection.ProtectEnchanted
                );

                SKSE::log::info(" ");
            }

            [[nodiscard]] static BGSListForm* GetJunkList() { return JunkList; }
            [[nodiscard]] static BGSListForm* GetUnjunkedList() { return UnjunkedList; }
            [[nodiscard]] static BGSKeyword* GetIsJunkKYWD() { return IsJunkKYWD; }

            [[nodiscard]] static bool ConfirmTransfer() { return JunkTransfer.ConfirmTransfer; }
            [[nodiscard]] static SortPriority GetTransferPriority() { return JunkTransfer.TransferPriority; }
            [[nodiscard]] static BGSListForm* GetTransferList() { return JunkTransfer.TransferList; }

            [[nodiscard]] static bool ConfirmSell() { return JunkSell.ConfirmSell; }
            [[nodiscard]] static SortPriority GetSellPriority() { return JunkSell.SellPriority; }
            [[nodiscard]] static BGSListForm* GetSellList() { return JunkSell.SellList; }

            [[nodiscard]] static bool ProtectEquipped() { return JunkProtection.ProtectEquipped; }
            [[nodiscard]] static bool ProtectFavorites() { return JunkProtection.ProtectFavorites; }
            [[nodiscard]] static bool ProtectEnchanted() { return JunkProtection.ProtectEnchanted; }

            [[nodiscard]] static float GetMarkJunkKey() { return MarkJunkKey; }
            [[nodiscard]] static float GetTransferJunkKey() { return TransferJunkKey; }

        private: 

            static inline float MarkJunkKey = 0x32;
            static inline float TransferJunkKey = 0x49;

            static inline BGSKeyword* IsJunkKYWD;
            static inline BGSListForm* JunkList;
            static inline BGSListForm* UnjunkedList;
            static inline JunkTransfer JunkTransfer;
            static inline JunkSell JunkSell;
            static inline JunkProtection JunkProtection;
    };   
}