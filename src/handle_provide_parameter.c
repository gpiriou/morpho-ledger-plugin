#include "morpho_plugin.h"

// Used to display corresponding payment token info (i.e cDAI -> DAI) for UI purposes. Edit here to add more tokens.
static void assign_token_info(ethPluginProvideParameter_t *msg, context_t *context)
{
    PRINTF("GPIRIOU ASSIGN TOKEN\n");
    uint8_t *pool_token_address = msg->parameter + 12;
    PRINTF("Pool token address: %.*H\n",
           ADDRESS_LENGTH,
           pool_token_address);
    if ((!memcmp(pool_token_address, CWETH_ADDRESS, ADDRESS_LENGTH)) || (!memcmp(pool_token_address, AWETH_ADDRESS, ADDRESS_LENGTH)))
    {
        memcpy(context->token_ticker, "WETH ", MAX_TICKER_LEN);
        context->token_decimals = 18;
    }
    else if ((!memcmp(pool_token_address, CUNI_ADDRESS, ADDRESS_LENGTH)) || (!memcmp(pool_token_address, AUNI_ADDRESS, ADDRESS_LENGTH)))
    {
        memcpy(context->token_ticker, "UNI ", MAX_TICKER_LEN);
        context->token_decimals = 18;
    }
    else if ((!memcmp(pool_token_address, CUSDC_ADDRESS, ADDRESS_LENGTH)) || (!memcmp(pool_token_address, AUSDC_ADDRESS, ADDRESS_LENGTH)))
    {
        memcpy(context->token_ticker, "USDC ", MAX_TICKER_LEN);
        context->token_decimals = 6;
    }
    else if ((!memcmp(pool_token_address, CDAI_ADDRESS, ADDRESS_LENGTH)) || (!memcmp(pool_token_address, ADAI_ADDRESS, ADDRESS_LENGTH)))
    {
        memcpy(context->token_ticker, "DAI ", MAX_TICKER_LEN);
        context->token_decimals = 18;
    }
    else if ((!memcmp(pool_token_address, CFEI_ADDRESS, ADDRESS_LENGTH)) || (!memcmp(pool_token_address, AFEI_ADDRESS, ADDRESS_LENGTH)))
    {
        memcpy(context->token_ticker, "FEI ", MAX_TICKER_LEN);
        context->token_decimals = 18;
    }
    else if ((!memcmp(pool_token_address, CWBTC_ADDRESS, ADDRESS_LENGTH)) || (!memcmp(pool_token_address, AWBTC_ADDRESS, ADDRESS_LENGTH)))
    {
        memcpy(context->token_ticker, "WBTC ", MAX_TICKER_LEN);
        context->token_decimals = 8;
    }
    else if ((!memcmp(pool_token_address, CUSDT_ADDRESS, ADDRESS_LENGTH)) || (!memcmp(pool_token_address, AUSDT_ADDRESS, ADDRESS_LENGTH)))
    {
        memcpy(context->token_ticker, "USDT ", MAX_TICKER_LEN);
        context->token_decimals = 6;
    }
    else if (!memcmp(pool_token_address, CCOMP_ADDRESS, ADDRESS_LENGTH))
    {
        memcpy(context->token_ticker, "COMP ", MAX_TICKER_LEN);
        context->token_decimals = 18;
    }
    else if (!memcmp(pool_token_address, AAAVE_ADDRESS, ADDRESS_LENGTH))
    {
        memcpy(context->token_ticker, "AAVE ", MAX_TICKER_LEN);
        context->token_decimals = 18;
    }
    else
    {
        memcpy(context->token_ticker, "? ", MAX_TICKER_LEN);
        context->token_decimals = DEFAULT_DECIMAL;
        context->token_warning = 1;
    }
}
static void handle_supply_and_repay(ethPluginProvideParameter_t *msg, context_t *context)
{
    PRINTF("GPIRIOU SUPPLY\n");
    switch ((supply_repay_parameters)context->next_param)
    {
    case _POOL_TOKEN_ADDRESS_SUPPLY_REPAY:
        assign_token_info(msg, context);
        break;
    case _ON_BEHALF:
        copy_address(context->on_behalf, msg->parameter, ADDRESS_LENGTH);
        break;
    case _AMOUNT_SUPPLY_REPAY:
        copy_parameter(context->amount, msg->parameter, sizeof(context->amount));
        break;
    default:
        PRINTF("Param not supported: %d\n", context->next_param);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        break;
    }
    context->next_param++;
}

static void handle_withdraw_and_borrow(ethPluginProvideParameter_t *msg, context_t *context)
{
    switch ((withdraw_borrow_parameters)context->next_param)
    {
    case _POOL_TOKEN_ADDRESS_WITHDRAW_BORROW:
        assign_token_info(msg, context);
        break;
    case _AMOUNT_WITHDRAW_BORROW:
        copy_parameter(context->amount, msg->parameter, sizeof(context->amount));
        break;
    default:
        PRINTF("Param not supported: %d\n", context->next_param);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        break;
    }
    context->next_param++;
}

static void handle_claim_rewards(ethPluginProvideParameter_t *msg, context_t *context)
{
    switch ((claim_rewards_parameters)context->next_param)
    {
    case OFFSET_C_TOKEN_ADDRESSES:
        break;
    case _TRADE_FOR_MORPHO_TOKEN:
        PRINTF("TRADE FOR MORPHO BOOL\n");
        PRINTF("LAST BYTE: %d\n", msg->parameter[PARAMETER_LENGTH - 1]);
        if (msg->parameter[PARAMETER_LENGTH - 1])
            context->trade_for_morpho = 1;
        break;
    case NONE:
        break;
    }
    context->next_param++;
}

void handle_provide_parameter(void *parameters)
{
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *)parameters;
    context_t *context = (context_t *)msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("___\nplugin provide parameter: offset %d\nBytes: \033[0;31m %.*H \033[0m \n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    PRINTF("GPIRIOU \n");
    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex)
    {
    case SUPPLY:
    case REPAY:
        handle_supply_and_repay(msg, context);
        break;
    case WITHDRAW:
    case BORROW:
        handle_withdraw_and_borrow(msg, context);
        break;
    case CLAIM_REWARDS:
        handle_claim_rewards(msg, context);
        break;
    default:
        PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        break;
    }
}