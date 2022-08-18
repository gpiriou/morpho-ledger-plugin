#include "morpho_plugin.h"
#include "text.h"

// Sets the first screen to display.
void handle_query_contract_id(void *parameters)
{
    ethQueryContractID_t *msg = (ethQueryContractID_t *)parameters;
    const context_t *context = (const context_t *)msg->pluginContext;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.

    // For the first screen, display the plugin name.
    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    PRINTF("GPIRIOU CONTRACT ID\n");
    // Get selector according screen.
    switch (context->selectorIndex)
    {
    case SUPPLY:
        strlcpy(msg->version, MSG_SUPPLY_ID, msg->versionLength);
        break;
    case REPAY:
        strlcpy(msg->version, MSG_REPAY_ID, msg->versionLength);
        break;
    case WITHDRAW:
        strlcpy(msg->version, MSG_WITHDRAW_ID, msg->versionLength);
        break;
    case BORROW:
        strlcpy(msg->version, MSG_BORROW_ID, msg->versionLength);
        break;
    case CLAIM_REWARDS:
        strlcpy(msg->version, MSG_CLAIM_REWARDS_ID, msg->versionLength);
        break;
    default:
        PRINTF("Selector index: %d not supported\n", context->selectorIndex);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}