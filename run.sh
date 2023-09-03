#!/bin/bash

# Verifica se foi fornecido um nome de arquivo como parâmetro
if [ $# -ne 1 ]; then
  echo "Uso: $0 <arquivo.cpp>"
  exit 1
fi

# Obtém o nome do arquivo de parâmetro
arquivo="$1"
nome_do_programa="${arquivo%.cpp}"

# Compila o programa C++
if g++ -o "$nome_do_programa" "$arquivo" -lglut -lGLU -lGL -lm ; then
  # Executa o programa se a compilação for bem-sucedida
  "./$nome_do_programa"
else
  echo "Erro ao compilar o programa."
fi