import pandas as pd
from datetime import datetime

def save_data(v, c, p, e, cost, alert):

    data = {
        "Timestamp":[datetime.now()],
        "Voltage":[v],
        "Current":[c],
        "Power":[p],
        "Energy":[e],
        "Cost":[cost],
        "Alert":[alert]
    }

    df = pd.DataFrame(data)

    df.to_csv(
        "data/energy_log.csv",
        mode="a",
        header=False,
        index=False
    )