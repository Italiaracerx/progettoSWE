#!/bin/bash
echo 'cd StudiodiFattibilità'
cd StudiodiFattibilità
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione StudiodiFattibilità fallita'
  exit 1
fi
echo 'cd PianodiQualifica'
cd ../PianodiQualifica
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione PianodiQualifica fallita'
  exit 1
fi
echo 'cd PianodiProgetto'
cd ../PianodiProgetto
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione PianodiProgetto fallita'
  exit 1
fi
echo 'cd NormediProgetto'
cd ../NormediProgetto
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione NormediProgetto fallita'
  exit 1
fi
echo 'cd AnalisideiRequisiti'
cd ../AnalisideiRequisiti
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione AnalisideiRequisiti fallita'
  exit 1
fi
echo 'cd Glossario'
cd ../Glossario
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione Glossario fallita'
  exit 1
fi
echo 'Documenti corretti'
