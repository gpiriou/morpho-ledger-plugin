#include "morpho_plugin.h"

static int find_selector(uint32_t selector, const uint32_t *selectors, size_t n, selector_t *out) {
    for (selector_t i = 0; i < n; i++) {
        if (selector == selectors[i]) {
            *out = i;
            return 0;
        }
    }
    return -1;
}

// Called once to init.
void handle_init_contract(void *parameters) {
    // Cast the msg to the type of structure we expect (here, ethPluginInitContract_t).
    ethPluginInitContract_t *msg = (ethPluginInitContract_t *) parameters;

    // Make sure we are running a compatible version.
    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        // If not the case, return the `UNAVAILABLE` status.
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Print size of plugin's context.
    PRINTF("context size: %d / %d\n", sizeof(context_t), msg->pluginContextLength);

    // Double check that the `context_t` struct is not bigger than the maximum size (defined by
    // `msg->pluginContextLength`).
    if (msg->pluginContextLength < sizeof(context_t)) {
        PRINTF("Plugin parameters structure is bigger than allowed size\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    context_t *context = (context_t *) msg->pluginContext;

    // Initialize the context (to 0).
    explicit_bzero(context, sizeof(*context));

    // Find tx selector
    uint32_t selector = U4BE(msg->selector, 0);
    if (find_selector(selector, MORPHO_SELECTORS, NUM_SELECTORS, &context->selectorIndex)) {
        PRINTF("can't find selector\n");
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Set `next_param` to be the first field we expect to parse.
    switch (context->selectorIndex) {
        case COMPOUND_SUPPLY:
            // Fallthrough
        case COMPOUND_REPAY:
            // Fallthrough
        case AAVE_SUPPLY:
            // Fallthrough
        case AAVE_REPAY:
            context->next_param = _POOL_TOKEN_ADDRESS_SUPPLY_REPAY;
            break;
        case COMPOUND_WITHDRAW:
            // Fallthrough
        case COMPOUND_BORROW:
            // Fallthrough
        case AAVE_WITHDRAW:
            // Fallthrough
        case AAVE_BORROW:
            context->next_param = _POOL_TOKEN_ADDRESS_WITHDRAW_BORROW;
            break;
        case COMPOUND_CLAIM_REWARDS:
            // Fallthrough
        case AAVE_CLAIM_REWARDS:
            context->next_param = OFFSET_C_TOKEN_ADDRESSES;
            break;
        case COMMON_CLAIM:
            context->next_param = _ACCOUNT;
            break;
        default:
            PRINTF("Missing selectorIndex: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    // Return valid status.
    msg->result = ETH_PLUGIN_RESULT_OK;
}
