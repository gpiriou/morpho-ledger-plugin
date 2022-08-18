#include "morpho_plugin.h"
#define PLUGIN_NAME "Morpho"

// Use this header file to simply modify the strings displayed.
// TITLE and MSG strings are respectively listed by order of appearance and used for the top and bottom text displays in the UI screen.

/* handle_query_contract_id.c strings */
// TITLE string for 1st UI is PLUGIN_NAME.

#define MSG_SUPPLY_ID "SUPPLY"
#define MSG_REPAY_ID "REPAY"
#define MSG_WITHDRAW_ID "WITHDRAW"
#define MSG_BORROW_ID "BORROW"
#define MSG_CLAIM_REWARDS_ID "Claim Rewards"

/* handle_query_contract_ui.c strings */

#define TITLE_SUPPLY_SCREEN_1_UI "Supplying"
#define TITLE_REPAY_SCREEN_1_UI "Repaying"
#define TITLE_WITHDRAW_SCREEN_1_UI "Withdrawing"
#define TITLE_BORROW_SCREEN_1_UI "Borrowing"
#define TITLE_CLAIM_REWARDS_SCREEN_1_UI "Claiming"
#define MSG_CLAIM_REWARDS_MORPHO_UI "Trading claimed tokens for Morpho."
#define MSG_CLAIM_REWARDS_OTHERS_UI "rewards"
#define TITLE_WARNING_UI "WARNING"
#define MSG_USER_WARNING_UI "Wrong user address!"
#define MSG_TOKEN_WARNING_UI "Unknown token!"