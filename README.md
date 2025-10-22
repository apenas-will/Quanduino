# Quanduino: Simulador para Ensino de Computação Quântica

## Sobre o Projeto

O **Quanduino** é um simulador baseado em Arduino desenvolvido para o ensino prático de computação quântica, com o objetivo de complementar as abordagens teóricas tradicionais. A escolha do Arduino fundamenta-se em sua capacidade de engajar estudantes e na familiaridade que alunos de tecnologia possuem com a plataforma.

Diferente dos métodos convencionais, que priorizam aspectos matemáticos, o Quanduino visa facilitar o aprendizado prático da computação quântica, tornando o campo mais acessível a estudantes e profissionais da área tecnológica.

## Motivação

A computação quântica tem sido tradicionalmente dominada por físicos com formação avançada, com os métodos de ensino tendo grande enfoque nos fundamentos matemáticos do campo. Apesar da crescente oferta de cursos online e materiais educativos, a lacuna entre teoria e prática ainda é um desafio. O Quanduino surge como uma potencial solução para essa problemática, proporcionando uma abordagem mais intuitiva e acessível ao ensino da computação quântica.

## Funcionalidades

O simulador permite que os usuários programem e executem circuitos quânticos em um ambiente físico, observando as operações e os estados dos qubits por meio de LEDs. As principais funcionalidades implementadas incluem:

- **Execução de circuitos quânticos**: O usuário pode modificar o código do simulador para definir um circuito quântico personalizado ou selecionar um circuito previamente implementado via terminal da Arduino IDE.

- **Representação visual dos estados quânticos**: LEDs indicam o estado dos qubits e a presença de superposição. Um LED lateral verde aceso indica que o sistema está em superposição, enquanto os LEDs superiores refletem os estados dos qubits após a medição.

- **Interação via _switch_**: O _switch_ posicionado no canto inferior direito do simulador permite ao usuário alternar entre o estado de superposição e a medição dos qubits.

- **Indicação de medição**: Ao realizar uma medição, o LED verde de superposição se apaga, e os LEDs superiores exibem os valores binários dos qubits. Caso o usuário altere o estado do _switch_ novamente, o LED de superposição reacende, permitindo uma nova medição.

## Como Começar

### Requisitos e materiais

- Arduino (Utilizou-se um Arduino Nano no projeto);
- Ambiente de Desenvolvimento Arduino IDE;
- 7 LEDs para representação dos qubits;
- 1 LED para representação do estado de superposição;
- 8 resistores de 100 $\Omega$
- _Switch_ ou botão;

### Instalação

1. Clone este repositório:
   ```sh
   git clone https://github.com/apenas-will/Quanduino.git
   ```
3. Faça o upload do código para o Arduino.
4. explore os experimentos disponíveis.

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests com melhorias e novas funcionalidades.

## Modificações
Este software foi originalmente criado por [Dakk](https://github.com/dakk) e está licenciado sob a Licença Apache 2.0.

As seguintes modificações foram feitas por Wildisley José de Souza Filho em março de 2025:
- Implementação de sistema para representação de superposição;
- Implementação de circuito para estado GHZ;
- Implementação de circuito do algoritmo de Deutsch-Jozsa para problema de Bernstein-Vazirani;
- Implementação de espaço para adição de novos circuitos personalizados.

## Referências

Caso utilize este projeto em publicações acadêmicas, cite com:

```
@misc{quanduino_repo,
  author = {Wildisley José de Souza Filho},
  title = {Quanduino: Simulador para ensino de computação quântica baseado em Arduino},
  year = {2025},
  url = {https://github.com/apenas-will/Quanduino}
}
```

---

Que o Quanduino possa ajudar a expandir os horizontes do ensino da computação quântica!
