.PHONY: datasets graficos all

DATASETS = libretas.txt gauss.txt uniforme.txt

all: datasets graficos

datasets: $(DATASETS)

%.txt: generar_datos.py
	python generar_datos.py $(patsubst %.txt,%,$@)

graficos: $(DATASETS)
	python graficar_datos.py
