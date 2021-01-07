echo "Python virtual environment creation script"
python -m venv .\.venv
echo "Virtual evnironment created"
cmd /k ".\.venv\Scripts\activate & pip install tensorflow numpy scikit-learn matplotlib pandas ipykernel" 
echo "Dependencies installed"