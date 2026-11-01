$stdout = "$env:TEMP\method-a-output.txt"
$stderr = "$env:TEMP\method-a-errors.txt"

$stopwatch = [System.Diagnostics.Stopwatch]::StartNew()

$process = Start-Process `
    -FilePath ".\ProvidedCode\method-a.exe" `
    -ArgumentList @(
        ".\data\data2-100MB.txt",
        ".\patterns\pattern2.txt"
    ) `
    -NoNewWindow `
    -PassThru `
    -RedirectStandardOutput $stdout `
    -RedirectStandardError $stderr

$process.WaitForExit()

$stopwatch.Stop()
$process.Refresh()

[PSCustomObject]@{
    "Real time (seconds)"   = [math]::Round($stopwatch.Elapsed.TotalSeconds, 6)
    "User time (seconds)"   = [math]::Round($process.UserProcessorTime.TotalSeconds, 6)
    "System time (seconds)" = [math]::Round($process.PrivilegedProcessorTime.TotalSeconds, 6)
    "Total CPU time (seconds)" = [math]::Round($process.TotalProcessorTime.TotalSeconds, 6)
    "Exit code"              = $process.ExitCode
}