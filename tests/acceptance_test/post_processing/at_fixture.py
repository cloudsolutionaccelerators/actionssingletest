import pytest
import pandas as pd
from asammdf import MDF

@pytest.fixture()
def at_fixture(mdf_file):
    with MDF(mdf_file) as mdf:
        signals = mdf.signals
        data = {(signal.name, i): value for signal in signals for i, value in enumerate(signal.samples)}
        dataframe = pd.DataFrame(data).T
        dataframe.index.names = ["signal", "timestamp"]
    return dataframe