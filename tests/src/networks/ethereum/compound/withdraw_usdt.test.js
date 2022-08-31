import { nano_models, processTest, populateTransaction } from "../../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x8888882f8f843896699869179fb6e4f7e3b58888";
const testNetwork = "ethereum";

const testLabel = "withdraw_usdt"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

// https://etherscan.io/tx/0x1cdd4770447bd29e8222bcc2d8a351c9bcaa3a229e58f7efe219ee30b9407a5b
const inputData = "0xf3fef3a3000000000000000000000000f650c3d88d12db855b8bf7d11be6c55a4e07dcc90000000000000000000000000000000000000000000000000000000031bad830";

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