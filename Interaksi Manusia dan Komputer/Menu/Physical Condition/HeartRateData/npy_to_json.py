import numpy as np
import json

# Mengganti path dengan path file .npy yang sesuai
npy_file_path = 'E:\PROJECT_IMK\Menu\Physical Condition\HeartRateData\heart_rate.npy'
json_file_path = 'output_file.json'

# Membaca array dari file .npy
data = np.load(npy_file_path)

# Memisahkan data menjadi lima pemain
num_players = 5
split_data = np.array_split(data, num_players, axis=0)

# Transpose data untuk mengubah kolom menjadi baris
transposed_data = np.array(split_data).T

# Konversi NumPy array menjadi Python list
data_list = transposed_data.tolist()

# Menyimpan data dalam format JSON
with open(json_file_path, 'w') as jsonfile:
    json.dump(data_list, jsonfile)