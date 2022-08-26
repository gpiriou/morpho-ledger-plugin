import { nano_models, processTest, populateTransaction } from "../../../../test.fixture";

const contractName = "Morpho";
const contractAddr = "0x777777c9898d384f785ee44acfe945efdff5f3e0";
const testNetwork = "ethereum";

const testLabel = "aave_claim_rewards"; // <= Name of the test
const testDirSuffix = testLabel.toLowerCase().replace(/\s+/g, '_');

// https://etherscan.io/tx/0xf3f77c6df2efe0a25d6357a28266d04151f983e102e1f691d764d6ee053fc715 but selector is modified (148e23ce -> 3111e7b3)
const inputData = "0x3111e7b300000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000800000000000000000000000035a18000230da775cac24873d00ff85bccded55000000000000000000000000039aa39c021dfbae8fac545936693ac917d5e75630000000000000000000000004ddc2d193948926d02f9b1fe9e1daa0718270ed50000000000000000000000005d3a536e4d6dbd6114cc1ead35777bab948e364300000000000000000000000070e36f6bf80a52b3b46b3af8e106cc0ed743e8e40000000000000000000000007713dd9ca933848f6819f38b8352d9a15ea73f67000000000000000000000000ccf4429db6322d5c611ee964527d42e5d685dd6a000000000000000000000000f650c3d88d12db855b8bf7d11be6c55a4e07dcc9";

const models = [
	{
		name: 'nanos',
		steps: 4
	},
	//{
	//	name: 'nanox',
	//	steps: 6
	//},
]

// populate unsignedTx from genericTx and get network chain id
const unsignedTx = populateTransaction(contractAddr, inputData, testNetwork);
// Process tests for each nano models
models.forEach((model) => {
	const nano_model = nano_models.find((nano_model) => nano_model.name === model.name)
	processTest(nano_model, model.steps, contractName, testLabel, testDirSuffix, unsignedTx, testNetwork)
})