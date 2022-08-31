#include "morpho_plugin.h"
#include "text.h"

static void handle_warning_ui(ethQueryContractUI_t *msg, context_t *context)
{
    if (context->token_warning && msg->screenIndex == 1)
    {
        strlcpy(msg->title, TITLE_WARNING_UI, msg->titleLength);
        strlcpy(msg->msg, MSG_TOKEN_WARNING_UI, msg->msgLength);
    }
    else if (context->user_warning)
    {
        switch (context->selectorIndex)
        {
        case COMPOUND_SUPPLY:
        case AAVE_SUPPLY:
        case COMPOUND_REPAY:
        case AAVE_REPAY:
            strlcpy(msg->title, TITLE_ON_BEHALF_UI, msg->titleLength);
            msg->msg[0] = '0';
            msg->msg[1] = 'x';
            getEthAddressStringFromBinary((uint8_t *)context->user_address,
                                          (uint8_t *)msg->msg + 2,
                                          msg->pluginSharedRW->sha3,
                                          0);
            break;
        default:
            strlcpy(msg->title, TITLE_WARNING_UI, msg->titleLength);
            strlcpy(msg->msg, MSG_USER_WARNING_UI, msg->msgLength);
            break;
        }
    }
    else
    {
        strlcpy(msg->title, "ERROR", msg->titleLength);
        strlcpy(msg->msg, "ERROR", msg->msgLength);
    }
}

static void handle_supply_ui(ethQueryContractUI_t *msg, context_t *context)
{
    switch (msg->screenIndex)
    {
    // Edit these cases to change screens.
    case 0:
        strlcpy(msg->title, TITLE_SUPPLY_UI, msg->titleLength);
        // displays ticker and amount.
        amountToString(context->amount, sizeof(context->amount),
                       context->token_decimals,
                       context->token_ticker,
                       msg->msg,
                       msg->msgLength);
        break;
    case 1:
    case 2:
        handle_warning_ui(msg, context);
        break;
    default:
        strlcpy(msg->title, "ERROR", msg->titleLength);
        strlcpy(msg->msg, "ERROR", msg->msgLength);
        break;
    }
}

static void handle_repay_ui(ethQueryContractUI_t *msg, context_t *context)
{
    switch (msg->screenIndex)
    {
    case 0:
        strlcpy(msg->title, TITLE_REPAY_UI, msg->titleLength);
        amountToString(context->amount, sizeof(context->amount),
                       context->token_decimals,
                       context->token_ticker,
                       msg->msg,
                       msg->msgLength);
        break;
    case 1:
    case 2:
        handle_warning_ui(msg, context);
        break;
    default:
        strlcpy(msg->title, "ERROR", msg->titleLength);
        strlcpy(msg->msg, "ERROR", msg->msgLength);
        break;
    }
}

static void handle_withdraw_ui(ethQueryContractUI_t *msg, context_t *context)
{
    switch (msg->screenIndex)
    {
    case 0:
        strlcpy(msg->title, TITLE_WITHDRAW_UI, msg->titleLength);
        amountToString(context->amount, sizeof(context->amount),
                       context->token_decimals,
                       context->token_ticker,
                       msg->msg,
                       msg->msgLength);
        break;
    default:
        strlcpy(msg->title, "ERROR", msg->titleLength);
        strlcpy(msg->msg, "ERROR", msg->msgLength);
        break;
    }
}

static void handle_borrow_ui(ethQueryContractUI_t *msg, context_t *context)
{
    switch (msg->screenIndex)
    {
    case 0:
        strlcpy(msg->title, TITLE_BORROW_UI, msg->titleLength);
        amountToString(context->amount, sizeof(context->amount),
                       context->token_decimals,
                       context->token_ticker,
                       msg->msg,
                       msg->msgLength);
        break;
    default:
        strlcpy(msg->title, "ERROR", msg->titleLength);
        strlcpy(msg->msg, "ERROR", msg->msgLength);
        break;
    }
}

static void handle_claim_rewards_ui(ethQueryContractUI_t *msg, context_t *context)
{
    switch (msg->screenIndex)
    {
    case 0:
        strlcpy(msg->title, TITLE_CLAIM_REWARDS_UI, msg->titleLength);
        if (context->trade_for_morpho)
            strlcpy(msg->msg, MSG_CLAIM_REWARDS_MORPHO_UI, msg->msgLength);
        else
            strlcpy(msg->msg, MSG_CLAIM_REWARDS_OTHERS_UI, msg->msgLength);
        break;
    default:
        strlcpy(msg->title, "ERROR", msg->titleLength);
        strlcpy(msg->msg, "ERROR", msg->msgLength);
        break;
    }
}
static void handle_claim_ui(ethQueryContractUI_t *msg, context_t *context)
{
    switch (msg->screenIndex)
    {
    case 0:
        strlcpy(msg->title, TITLE_CLAIM_REWARDS_UI, msg->titleLength);
        strlcpy(msg->msg, MSG_CLAIM_UI, msg->msgLength);
        break;
    case 1:
        handle_warning_ui(msg, context);
        break;
    default:
        strlcpy(msg->title, "ERROR", msg->titleLength);
        strlcpy(msg->msg, "ERROR", msg->msgLength);
        break;
    }
}

void handle_query_contract_ui(void *parameters)
{
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *)parameters;
    context_t *context = (context_t *)msg->pluginContext;

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex)
    {
    case COMPOUND_SUPPLY:
    case AAVE_SUPPLY:
        handle_supply_ui(msg, context);
        break;
    case COMPOUND_REPAY:
    case AAVE_REPAY:
        handle_repay_ui(msg, context);
        break;
    case COMPOUND_WITHDRAW:
    case AAVE_WITHDRAW:
        handle_withdraw_ui(msg, context);
        break;
    case COMPOUND_BORROW:
    case AAVE_BORROW:
        handle_borrow_ui(msg, context);
        break;
    case COMPOUND_CLAIM_REWARDS:
    case AAVE_CLAIM_REWARDS:
        handle_claim_rewards_ui(msg, context);
        break;
    case COMMON_CLAIM:
        handle_claim_ui(msg, context);
        break;
    default:
        PRINTF("Error in handle_query_contract_ui's selectorIndex switch\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        break;
    }
}
