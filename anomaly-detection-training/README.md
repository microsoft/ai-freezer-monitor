# Machine Learning Training Notebook

After you have 30 days of data from your freezer you can use it to train a Machine Learning model. The goal of this model is be able to warn you before the freezer fails rather than after the tempereature is already too high. To do this we're going to use an autoencoder algorithem.

## About Autoencoders

An autoencoder is a type of compression algorithem that work really well on the type of data it's trained on, and not so well on all other data. For anomaly detection you can use this charateristic of the alogrithem to check whether new data is similar to or different than the training data used. The model is build using two parts, an encoder, which compresses the data, and a decoder, which uncpresses the data. Then you can check the accuracy of the recreation of the data. A high error rate is likely an anomaly in the operation of the device.

## Further Reading
https://keras.io/examples/timeseries/timeseries_anomaly_detection/
https://www.tensorflow.org/tutorials/generative/autoencoder
https://github.com/ShawnHymel/tinyml-example-anomaly-detection