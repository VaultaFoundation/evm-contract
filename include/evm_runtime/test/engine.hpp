#pragma once
#include <silkworm/core/protocol/rule_set.hpp>
#include <silkworm/core/protocol/param.hpp>

using namespace silkworm::protocol;

namespace evm_runtime {
namespace test {

class engine : public RuleSet {
  public:
    explicit engine(const ChainConfig& chain_config) : RuleSet(chain_config, /*prohibit_ommers=*/false) {}

    void initialize(EVM& evm) override {}
    ValidationResult validate_difficulty_and_seal(const BlockHeader&, const BlockHeader&) override {
        return ValidationResult::kOk;
    }

    ValidationResult finalize(IntraBlockState& state, const Block& block, EVM& evm, const std::vector<Log>& logs) override {
        // const BlockReward reward{compute_reward(block)};
        // state.add_to_balance(get_beneficiary(block.header), reward.miner);
        // for (size_t i{0}; i < block.ommers.size(); ++i) {
        //     state.add_to_balance(block.ommers[i].beneficiary, reward.ommers[i]);
        // }
        return ValidationResult::kOk;
    }

    //! \brief Performs validation of block body that can be done prior to sender recovery and execution.
    //! \brief See [YP] Sections 4.3.2 "Holistic Validity" and 11.1 "Ommer Validation".
    //! \param [in] block: block to pre-validate.
    //! \param [in] state: current state.
    //! \note Shouldn't be used for genesis block.
    ValidationResult pre_validate_block_body(const Block& block, const BlockState& state) override {
        (void)block;
        (void)state;
        return ValidationResult::kOk;
    }

    //! \brief See [YP] Section 4.3.4 "Block Header Validity".
    //! \param [in] header: header to validate.
    //! \param [in] with_future_timestamp_check : whether to check header timestamp is in the future wrt host current
    //! time \see https://github.com/torquem-ch/silkworm/issues/448
    //! \note Shouldn't be used for genesis block.
    ValidationResult validate_block_header(const BlockHeader& header, const BlockState& state,
                                           bool with_future_timestamp_check) override {
        (void)header;
        (void)state;
        (void)with_future_timestamp_check;
        return ValidationResult::kOk;
    }

    //! \brief Performs validation of block ommers only.
    //! \brief See [YP] Sections 11.1 "Ommer Validation".
    //! \param [in] block: block to validate.
    //! \param [in] state: current state.
    ValidationResult validate_ommers(const Block& block, const BlockState& state) override {
        (void)block;
        (void)state;
        return ValidationResult::kOk;
    }

    //! \brief See [YP] Section 11.3 "Reward Application".
    //! \param [in] header: Current block to get beneficiary from
    evmc::address get_beneficiary(const BlockHeader& header) override {
        return header.beneficiary;
    };

    //! \brief Returns parent header (if any) of provided header
    static std::optional<BlockHeader> get_parent_header(const BlockState& state, const BlockHeader& header) {
        (void)state;
        (void)header;
        return {};
    }
};

} //namespace test
} //namespace evm_runtime