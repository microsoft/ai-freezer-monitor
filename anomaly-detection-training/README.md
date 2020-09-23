# Machine Learning Training Notebook

After you have 30 days of data from your freezer you can use it to train a Machine Learning model. The goal of this model is be able to warn you before the freezer fails rather than after the tempereature is already too high. To do this we're going to use an autoencoder algorithem.

## About Autoencoders

An autoencoder is a type of compression algorithm that works well on the type of data it's trained on, but not so well on any other data. For anomaly detection, you can use this characteristic of the algorithm to check whether new data is similar to or different than the training data used. 

The model is built using two parts: 1) an encoder, which compresses the data, and 2) a decoder, which decompresses the data. Decompression allows you to check the accuracy of the re-created data. A high error rate in re-created data is likely an anomaly.

## Further Reading
https://keras.io/examples/timeseries/timeseries_anomaly_detection/
https://www.tensorflow.org/tutorials/generative/autoencoder
https://github.com/ShawnHymel/tinyml-example-anomaly-detection
