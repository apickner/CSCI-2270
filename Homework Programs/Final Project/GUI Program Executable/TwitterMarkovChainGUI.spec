# -*- mode: python -*-

block_cipher = None


a = Analysis(['TwitterMarkovChainGUI.py'],
             pathex=['/Users/AndrewMacbook/Documents/Csci 2270/Homework Programs/Final Project/GUI Program copy'],
             binaries=[],
             datas=[],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          [],
          name='TwitterMarkovChainGUI',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          runtime_tmpdir=None,
          console=False )
app = BUNDLE(exe,
             name='TwitterMarkovChainGUI.app',
             icon=None,
             bundle_identifier=None)
