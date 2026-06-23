@echo off
cd /d "C:\Users\lucca.dotti\Downloads\4_lab3\LabPA"
echo. > git_log.txt

echo === eliminar locks === >> git_log.txt
if exist ".git\index.lock" del /f ".git\index.lock" >> git_log.txt 2>&1
if exist ".git\objects\maintenance.lock" del /f ".git\objects\maintenance.lock" >> git_log.txt 2>&1

echo === add all === >> git_log.txt
git add -A >> git_log.txt 2>&1

echo === commit === >> git_log.txt
git commit -m "Validaciones: TipoRet en input, restricciones dominio, diagrama arquitectura" >> git_log.txt 2>&1

echo === pull rebase === >> git_log.txt
git pull origin main --rebase >> git_log.txt 2>&1

echo === push === >> git_log.txt
git push origin main >> git_log.txt 2>&1

echo === log final === >> git_log.txt
git log --oneline -5 >> git_log.txt 2>&1

echo DONE >> git_log.txt
type git_log.txt
pause
