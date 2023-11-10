# ULFCom

<img src="data/images/logo.svg" width="20%" align="right">

ZSU is a German acronym for ZIMO Sammel Update (ZIMO Collective Update), a file format for firmware updates. The format supports multiple, optionally [Salsa20](https://github.com/ZIMO-Elektronik/Salsa20) encrypted, firmwares for a variety of target devices. ZSU files are currently used by the following products:
- Command stations
  - [ZIMO MXULF](http://www.zimo.at/web2010/products/InfMXULF_EN.htm)

<details>
  <summary>Table of contents</summary>
  <ol>
    <li><a href="#file-format-specification">File format specification</a></li>
      <ul>
        <li><a href="#header">Header</a></li>
        <li><a href="#firmware-data">Firmware data</a></li>
      </ul>
    <li><a href="#getting-started">Getting started</a></li>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#build">Build</a></li>
      </ul>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>

![alt_text](data/images/ulfcom.png)