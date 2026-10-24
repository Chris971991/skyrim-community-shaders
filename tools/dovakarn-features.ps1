# Copies the Community Shaders features Dovakarn serves to its players out of this fork, at the fork's own commit, into
# <Out>\Shaders (the layout of a game's Data folder): each feature's Shaders\Features\<Name>.ini and its shader folder.
# The DLL is built from the same commit (DOVAKARN-BUILD.md), so the shaders always match the plugin that compiles them.
#   powershell -File tools\dovakarn-features.ps1 -Out <folder>
# Dovakarn copies them into its server's player-settings folder (skyrp server-admin/player-settings/Shaders).
param([Parameter(Mandatory)][string]$Out)
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
# The features served (folder under features\). Not served: Terrain Helper (needs its own plugin, TerrainHelper.esp),
# Exponential Height Fog (unreleased in 1.8.3, off by default with no tuned look).
# Screen-Space Shadows is a core feature (the Nexus download has it too); it is served because Dovakarn changed it (its
# distance fade, DOVAKARN_CHANGES.txt), and its shaders must match this DLL's constant buffer.
$features = @('Wetness Effects', 'Skylighting', 'Terrain Blending', 'Terrain Variation', 'Screen Space GI', 'Screen-Space Shadows')
foreach ($f in $features) {
  $src = Join-Path $root "features\$f\Shaders"
  if (-not (Test-Path $src)) { throw "$f has no Shaders folder at $src" }
  foreach ($file in Get-ChildItem $src -Recurse -File) {
    $rel = $file.FullName.Substring($src.Length + 1)
    $dest = Join-Path $Out "Shaders\$rel"
    New-Item -ItemType Directory -Force (Split-Path -Parent $dest) | Out-Null
    Copy-Item $file.FullName $dest -Force
    "Shaders\$rel"
  }
}
