# Machine Learning Training Notebook

Once you have 30 days of data from your freezer, you're ready to train a custom Machine Learning (ML) model! The goal of this model is to warn you before a freezer fails, giving you time to address the failure prior to losing critical work. To do this we'll use an auto-encoder algorithm.

## About Autoencoders

An autoencoder is a type of compression algorithm that works well on the type of data it's trained on, but not so well on any other data. For anomaly detection, you can use this characteristic of the algorithm to check whether new data is similar to or different than the training data used. 

The model is built using two parts: 1) an encoder, which compresses the data, and 2) a decoder, which decompresses the data. Decompression allows you to check the accuracy of the re-created data. A high error rate in re-created data is likely an anomaly.

## Further Reading
* [Autoencoder example from Keras](https://keras.io/examples/timeseries/timeseries_anomaly_detection/)
* [Autoencoder example from TensorFlow](https://www.tensorflow.org/tutorials/generative/autoencoder)
* [Anomaly detection project by Shawn Hymel](https://github.com/ShawnHymel/tinyml-example-anomaly-detection)
