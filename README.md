# AI Freezer Monitor
The AI Freezer Monitor is a diy IoT monitor that uses machine learning to provide early warnings of potential equiepment failure. The project covers building the device from readily avialable compoenents, collecting data, setting up email alerts, training an auto encoder machine learning model, and depolying the model to an ESP32 development board. The project is designed to be in with ultra low temperature scientific freezers, with the goal of reducing the need to keep backup freezers running full time. That said this project has not gone through extensive testing and should be relyed on in critical applications before you are certain that it is performing as expected on your equipment. As more people use this and contribute improvements to this project we will be able to increas the efficacy of this accross different devices.

>The project should take between two and three hours to complete, but the device will need to passivly collect temperature data for 30 days before you will be able to train the model.

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
