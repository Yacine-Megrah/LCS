$progName = $args[0]

gcc "src\$progName.c -o bin\$($progName).exe"

.\bin\$($progName).exe
