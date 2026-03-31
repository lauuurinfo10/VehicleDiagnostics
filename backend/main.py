import json
import os
import numpy as np
from fastapi import FastAPI,HTTPException
from fastapi.responses import HTMLResponse
from pydantic import BaseModel
from typing import List
from sklearn.ensemble import IsolationForest

app = FastAPI(title="Vehicle Diagnostics API")

class SensorData(BaseModel):
    sensor: str
    value: float
    anomaly: bool


class VehicleReading(BaseModel):
    reading_number: int
    readings: List[SensorData]

@app.get("/",response_class=HTMLResponse)
def read_root():
    with open("index.html","r") as f:
        return f.read()


@app.get("/api/readings")
def get_latest_readings(limit:int=5):
    file_path="../data/readings.json"

    if not os.path.exists(file_path):
        raise HTTPPException(status_code=404,detail="Fisierul cu date nu a fost gasit.Ai rulat simulatorul C++?")
    
    valid_readings=[]

    with open (file_path,"r") as file:
        lines=file.readlines()

        for line in lines[-limit:]:
            if(line.strip):
                valid_readings.append(VehicleReading(**json.loads(line)))

    return {"status": "success", "data": valid_readings}


@app.get("/api/analyze/{sensor_name}")
def analyze_sensor_data(sensor_name:str):
    file_path="../data/readings.json"
    if not os.path.exists(file_path):
        raise HTTPException(status_code=404,detail="Fisierul cu date nu a fost gasit. ")
    
    sensor_values=[]
    actual_anomaly_flags=[]

    with open(file_path,"r") as file:
            lines=file.readlines()[-300:]
            for line in lines:
                if line.strip():
                    reading=json.loads(line)
                    for s in reading["readings"]:
                        if s["sensor"].upper()==sensor_name.upper():
                            sensor_values.append(s["value"])
                            actual_anomaly_flags.append(s["anomaly"])
                        
                    
    if len(sensor_values)<20:
        return {"error":"Nu sunt destule date pentru antrenarea ML.Lasa simulatorul C++ sa ruleze mai mult!"}
    
    X=np.array(sensor_values).reshape(-1,1)
    model=IsolationForest(contamination=0.05,random_state=42)
    model.fit(X)

    latest_value=sensor_values[-1]
    cpp_flag=actual_anomaly_flags[-1]

    prediction=model.predict([[latest_value]])[0]
    is_ml_anomaly=bool(prediction==-1)

    return{
        "sensor": sensor_name.upper(),
        "latest_value": latest_value,
        "cpp_ground_truth": cpp_flag,
        "ml_prediction": is_ml_anomaly,
        "ml_is_correct": cpp_flag == is_ml_anomaly,
        "historical_data_points_analyzed": len(sensor_values)
    }
    