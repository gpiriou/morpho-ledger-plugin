#include "morpho_plugin.h"
#include "text.h"

static void handle_supply_ui(ethQueryContractUI_t *msg, context_t *context)
{
    switch (msg->screenIndex)
    {
    // Edit these cases to change screens.
    case 0:
        strlcpy(msg->title, TITLE_SUPPLY_SCREEN_1_UI, msg->titleLength);
        // displays ticker and amount.
        amountToString(context->amount, sizeof(context->amount),
                       context->token_decimals,
                       context->token_ticker,
                       msg->msg,
                       msg->msgLength);
        break;
    case 1:
        strlcpy(msg->title, TITLE_WARNING_UI, msg->titleLength);
        if (context->token_warning)
            strlcpy(msg->msg, MSG_TOKEN_WARNING_UI, msg->msgLength);
        else
            strlcpy(msg->msg, MSG_USER_WARNING_UI, msg->msgLength);
        break;
    case 2:
        strlcpy(msg->title, TITLE_WARNING_UI, msg->titleLength);
        strlcpy(msg->msg, MSG_USER_WARNING_UI, msg->msgLength);
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
        strlcpy(msg->title, TITLE_REPAY_SCREEN_1_UI, msg->titleLength);
        amountToString(context->amount, sizeof(context->amount),
                       context->token_decimals,
                       context->token_ticker,
                       msg->msg,
                       msg->msgLength);
        break;
    case 1:
        strlcpy(msg->title, TITLE_WARNING_UI, msg->titleLength);
        if (context->token_warning)
            strlcpy(msg->msg, MSG_TOKEN_WARNING_UI, msg->msgLength);
        else
            strlcpy(msg->msg, MSG_USER_WARNING_UI, msg->msgLength);
        break;
    case 2:
        strlcpy(msg->title, TITLE_WARNING_UI, msg->titleLength);
        strlcpy(msg->msg, MSG_USER_WARNING_UI, msg->msgLength);
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
        strlcpy(msg->title, TITLE_WITHDRAW_SCREEN_1_UI, msg->titleLength);
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
        strlcpy(msg->title, TITLE_BORROW_SCREEN_1_UI, msg->titleLength);
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
        strlcpy(msg->title, TITLE_CLAIM_REWARDS_SCREEN_1_UI, msg->titleLength);
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

void handle_query_contract_ui(void *parameters)
{
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *)parameters;
    context_t *context = (context_t *)msg->pluginContext;

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    msg->result = ETH_PLUGIN_RESULT_OK;

    // Get corresponding screen (except for claim rewards).
    switch (context->selectorIndex)
    {
    case SUPPLY:
        handle_supply_ui(msg, context);
        break;
    case REPAY:
        handle_repay_ui(msg, context);
        break;
    case WITHDRAW:
        handle_withdraw_ui(msg, context);
        break;
    case BORROW:
        handle_borrow_ui(msg, context);
        break;
    case CLAIM_REWARDS:
        handle_claim_rewards_ui(msg, context);
        break;
    default:
        PRINTF("Error in handle_query_contract_ui's selectorIndex switch\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        break;
    }
}
