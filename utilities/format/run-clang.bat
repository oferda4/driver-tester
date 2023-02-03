set code_dirs="usermode" "kernelmode" "runner" "test"
cd ..\..

for %%d in (%code_dirs%) do (
    cd %%d
    for /r %%t in (*.cpp *.h *.inl) do clang-format -i -style=file "%%t"
    cd ..
)

pause