# Copyright (C) 2021 Intel Corporation

FROM openvino/model_server:2021.4.1-gpu
USER root 
RUN apt-get update && apt-get install -y --no-install-recommends \
    wget \
    python3-pip

RUN mkdir -p /opt/models/vehicle_detection_adas/1 && cd /opt/models/vehicle_detection_adas/1 && \
    wget https://storage.openvinotoolkit.org/repositories/open_model_zoo/2021.4/models_bin/3/vehicle-detection-adas-0002/FP32/vehicle-detection-adas-0002.bin && \
    wget https://storage.openvinotoolkit.org/repositories/open_model_zoo/2021.4/models_bin/3/vehicle-detection-adas-0002/FP32/vehicle-detection-adas-0002.xml && \
    mkdir -p /opt/models/vehicle_attributes/1 && cd /opt/models/vehicle_attributes/1 && \
    wget https://storage.openvinotoolkit.org/repositories/open_model_zoo/2021.4/models_bin/3/vehicle-attributes-recognition-barrier-0039/FP32/vehicle-attributes-recognition-barrier-0039.bin && \
    wget https://storage.openvinotoolkit.org/repositories/open_model_zoo/2021.4/models_bin/3/vehicle-attributes-recognition-barrier-0039/FP32/vehicle-attributes-recognition-barrier-0039.xml && \
    mkdir -p /opt/models/person_vehicle_bike_detection/1 && cd /opt/models/person_vehicle_bike_detection/1 && \
    wget https://storage.openvinotoolkit.org/repositories/open_model_zoo/2021.4/models_bin/3/person-vehicle-bike-detection-crossroad-0078/FP32/person-vehicle-bike-detection-crossroad-0078.bin && \
    wget https://storage.openvinotoolkit.org/repositories/open_model_zoo/2021.4/models_bin/3/person-vehicle-bike-detection-crossroad-0078/FP32/person-vehicle-bike-detection-crossroad-0078.xml && \
    mkdir -p /opt/models/face_detection_adas/1 && cd /opt/models/face_detection_adas/1 && \
    wget https://storage.openvinotoolkit.org/repositories/open_model_zoo/2021.4/models_bin/3/face-detection-adas-0001/FP32/face-detection-adas-0001.bin && \
    wget https://storage.openvinotoolkit.org/repositories/open_model_zoo/2021.4/models_bin/3/face-detection-adas-0001/FP32/face-detection-adas-0001.xml


COPY src/ams_wrapper/  /ams_wrapper/
COPY src/ams_models /ams_models
COPY src/start_ams.sh /start_ams.sh
COPY licensing /licensing



RUN pip3 install --upgrade pip && pip3 install --no-cache-dir -r /ams_wrapper/requirements.txt

RUN chmod +x /ams_wrapper/start_ams.py

USER ovms

ENTRYPOINT ["bash", "/start_ams.sh"]