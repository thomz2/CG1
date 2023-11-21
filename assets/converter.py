from PIL import Image

def convert_rgba_to_rgb(input_path, output_path):
    # Abre a imagem
    img = Image.open(input_path)

    # Converte a imagem para o modo 'RGB' (removendo o canal alfa)
    rgb_img = img.convert('RGB')

    # Salva a nova imagem
    rgb_img.save(output_path)

# Exemplo de uso
input_path = 'assets/roll/Roll_(Cutscene).png'
output_path = 'assets/roll/Roll_(Cutscene)_rgb.png'

# assets\megaman\Megaman.png

convert_rgba_to_rgb(input_path, output_path)
