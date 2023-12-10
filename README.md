# O problema das 8 rainhas
## Definição do problema
Colocar 8 rainhas em um tabuleiro de xadrez de tal maneira que nenhuma das rainhas ataque qualquer outra rainha, evidentemente respeitando as regras do jogo 
Este tipo de problema não tem uma solução analítica, é preciso usar força-bruta, então esse algoritmo pe feito com base em testar diversas possibilidades até achar
uma posição no tabuleiro de xadrez que contenha as 8 rainhas onde cada uma não esteja atacada por outra

## Exemplos

### Errado
![exemploErrado.](/imagemExemploErrado.PNG)

Nesse exemplo, percebe-se que as duas rainhas estão na mesma diagonal, "atacando" uma a outra, logo elas não obedecem a regra proposta pelo problema.

### Certo

![exemploCerto.](/imagemExemploCerto.PNG)

Nesse exemplo, as duas rainhas não estão em casas atacadas pela outra, então elas obedecem a regra proposta pelo problema.

## Resultado

