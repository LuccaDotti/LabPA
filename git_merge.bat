@echo off
cd /d "C:\Users\lucca.dotti\Downloads\4_lab3\LabPA"

echo === eliminar locks ===
if exist ".git\index.lock" del /f ".git\index.lock"
if exist ".git\objects\maintenance.lock" del /f ".git\objects\maintenance.lock"

echo === add all ===
git add -A

echo === commit ===
git commit -m "Validaciones: TipoRet en input, restricciones dominio, diagrama arquitectura"

echo === restaurar git_log.txt para limpiar unstaged ===
git restore git_log.txt 2>nul
git restore git_merge.bat 2>nul

echo === pull rebase ===
git pull origin main --rebase

echo === push ===
git push origin main

echo === log final ===
git log --oneline -5

echo DONE
pause
