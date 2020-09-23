# AI Freezer Monitor
The AI Freezer Monitor is a DIY IoT monitor that uses machine learning, or ML, to provide early warnings of potential equipment failure. This guide covers building the device, collecting training data, setting up email alerts, training a custom auto encoder machine learning model, and deploying the model to an ESP32 development board. 

The project is designed to be functional for low temperature scientific freezers (-60 C), with the goal of reducing  catastrophic failure and the need to keep backup freezers running full-time. However, please note that this project is primarily for demonstrative and educational purposes and has not gone through extensive testing. 

>This project takes about two to three hours to fully complete. Please note that the device will need to passively collect temperature data for about 30 days before you will be able to train the model.

# Contents

| Part | Link | Time |
|------|------|------|
| Data Collection and Alerts | [IoT Freezer Monitor](/FreezerTempAlert) | 60-90 minutes |
| Training ML Model | [Auto Encoder Training Notebook](/anomaly-detection-training/autoencoder_training.ipynb) | 30-45 minutes |
| Deploying Model | [AI Freezer Monitor](/AIFreezerMonitor) | 30-45 minutes|

# Contributing

This project welcomes contributions and suggestions.  Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.opensource.microsoft.com.

When you submit a pull request, a CLA bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., status check, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.
