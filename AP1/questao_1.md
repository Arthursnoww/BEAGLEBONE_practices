## RESPOSTA:

A primeira imagem mostra o processo de desenvolvimento de software embarcado, na qual os arquivos de origem(.c/.cpp/.masm ...) são compilados ou montados para um arquivo objeto(.o) depois os arquivos são copilados juntos, gerando um único arquivo objeto através de um programa relocável ou ligador(LINKER), onde endereços físicos são atribuídos aos deslocamento relativo desse programa unificado através de um processo de realocação que gera um arquivo executável (.exe) para rodar no sistema embarcado.

depois do arquivo executável esta armazenado no computador HOST, o .exe é transferido para um sistema incorporado e executado. na segundo imagem temos o computador HOST e alguns tipos e ferramentas de depuração, como:

DEPURADORES REMOTOS: monitoram e controlam o estado do software incorporado através de portas seriais ou conexão de rede entre o host e o destino (ex: link de comunicação).

EMULADOR DE CIRCUITO: permite que você examine o estado do processador no qual esse programa está sendo executado.

SIMULADOR: é um programa totalmente baseado em host que simula a funcionalidade e o conjunto de instruções do processador de destino.
