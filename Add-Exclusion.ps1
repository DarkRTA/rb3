Start-Process -Verb RunAs -Wait powershell.exe -Args @"
  `$dir=\`"${pwd}\`"
  Write-Output \`"Adding exclusion path to Windows Defender: `${dir}\`"
  Add-MpPreference -ExclusionPath \`"`${dir}\`"
  `$result = if (`$?)
  {
    \`"Command succeeded\`"
  }
  else
  {
    \`"Command failed\`"
  }
  Write-Output `$result
  read-host \`"Press enter to exit\`"
"@
