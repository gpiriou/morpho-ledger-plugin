import { nano_models, processTest, populateTransaction } from "../../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x777777c9898d384f785ee44acfe945efdff5f3e0";
const testNetwork = "ethereum";

const testLabel = "aave_borrow"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

// https://etherscan.io/tx/0xe1d86e2445ea26eaf4c5232e9973d2054fd55daba2cea43eae4ca283fedf8a88
const inputData = "0x4b8a3529000000000000000000000000030ba81f1c18d280636f32af80b9aad02cf0854e000000000000000000000000000000000000000000000000011b874008897b00";

const models = [
	{
		name: 'nanos',
		steps: 4
	},
]

// populate unsignedTx from genericTx and get network chain id
const unsignedTx = populateTransaction(contractAddr, inputData, testNetwork);
// Process tests for each nano models
models.forEach((model) => {
	const nano_model = nano_models.find((nano_model) => nano_model.name === model.name)
	processTest(nano_model, model.steps, contractName, testLabel, testDirSuffix, unsignedTx, testNetwork)
})