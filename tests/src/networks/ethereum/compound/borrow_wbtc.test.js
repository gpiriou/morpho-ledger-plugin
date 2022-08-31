import { nano_models, processTest, populateTransaction } from "../../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x8888882f8f843896699869179fb6e4f7e3b58888";
const testNetwork = "ethereum";

const testLabel = "borrow_wbtc"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

// https://etherscan.io/tx/0x07eb806a072a8ee6f4247466f0fb17dacb0d320e74f21c22567e7d79c2d14ae9
const inputData = "0x4b8a3529000000000000000000000000ccf4429db6322d5c611ee964527d42e5d685dd6a0000000000000000000000000000000000000000000000000000000029b92700";

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