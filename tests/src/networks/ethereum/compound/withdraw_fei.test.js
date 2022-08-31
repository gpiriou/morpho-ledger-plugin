import { nano_models, processTest, populateTransaction } from "../../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x8888882f8f843896699869179fb6e4f7e3b58888";
const testNetwork = "ethereum";

const testLabel = "withdraw_fei"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

// https://etherscan.io/tx/0xabcb0fbd20437007dbd3b5c05d7aa001fba0eb25c9cf4b632350ea1eeb8afba7
const inputData = "0xf3fef3a30000000000000000000000007713dd9ca933848f6819f38b8352d9a15ea73f67000000000000000000000000000000000000000000000037111d0c7cd900e8b8";

const models = [
	{
		name: 'nanos',
		steps: 6
	},
]

// populate unsignedTx from genericTx and get network chain id
const unsignedTx = populateTransaction(contractAddr, inputData, testNetwork);
// Process tests for each nano models
models.forEach((model) => {
	const nano_model = nano_models.find((nano_model) => nano_model.name === model.name)
	processTest(nano_model, model.steps, contractName, testLabel, testDirSuffix, unsignedTx, testNetwork)
})