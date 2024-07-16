import os
import time
import json
import pytest
import pandas as pd

def test_chalfont_shop_layout():
    sdf_file = "world_models/example.csv"
    sdf_file = os.path.abspath(sdf_file)

    assert os.path.exists(sdf_file)
    df = pd.read_csv(sdf_file)

    assert isinstance(df, pd.DataFrame)
    start_time = time.time()
    elapsed_time = 0.0

    # Read the moves file
    file = 'csv_files/ChalfontShopLayout_Moves.csv'
    assert os.path.exists(file)
    file = os.path.abspath(file)
    moves = pd.read_csv(file)

    # Read the nodes file
    file = 'csv_files/ChalfontShopLayout_Nodes.csv'
    assert os.path.exists(file)
    file = os.path.abspath(file)
    nodes = pd.read_csv(file, skipinitialspace=True)

    scenario_file = os.path.abspath('test_scenario.json')
    with open(scenario_file, 'r') as f:
        data = json.load(f)
        simulation_time = float(data['simulation_duration'])

        while elapsed_time < simulation_time:
            for item in data['hostInput']:
                secs = float(item['endTime'])

                if elapsed_time == secs:
                    id = item['value'][0]
                    rows = moves.loc[moves['Move ID'].str.contains(id)]
                    end_node = rows['End Node ID'].values[0]

                    row = nodes.loc[nodes['Node ID'] == end_node]
                    X = row['X (m)'].values[0]
                    Y = row['Y (m)'].values[0]
                    Heading = row['Path Heading (deg)'].values[0]
                    row = df.loc[df['timestamp'] == elapsed_time]
                    x = row['X']
                    x = float(x.iloc[0])
                    y = row['Y']
                    y = float(y.iloc[0])
                    heading = row['Heading']
                    heading = float(heading.iloc[0])
                    assert (round(x,2) == round(X,2))
                    assert (round(y,2) == round(Y,2))
                    assert (round(heading,2) == round(Heading,2))

            elapsed_time = round(time.time() - start_time, 2)
        
    print(f"All tests have passed ...")