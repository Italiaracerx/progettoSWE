#!/bin/bash
echo 'cd StudiodiFattibilità'
cd StudiodiFattibilità
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione StudiodiFattibilità fallita'

fi
echo 'cd PianodiQualifica'
cd ../PianodiQualifica
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione PianodiQualifica fallita'

fi
echo 'cd PianodiProgetto'
cd ../PianodiProgetto
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione PianodiProgetto fallita'

fi
echo 'cd NormediProgetto'
cd ../NormediProgetto
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione NormediProgetto fallita'

fi
echo 'cd AnalisideiRequisiti'
cd ../AnalisideiRequisiti
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione AnalisideiRequisiti fallita'

fi
echo 'cd Glossario'
cd ../Glossario
if ! pdflatex -interaction=nonstopmode -halt-on-error *.tex
then
  echo 'compilazione Glossario fallita'

fi
echo 'Documenti corretti'
