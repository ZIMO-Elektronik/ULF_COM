# ULFCom

<img src="data/images/logo.svg" width="20%" align="right">

The [ZIMO MXULF](http://www.zimo.at/web2010/products/InfMXULF_EN.htm), a device for updating and testing model train decoders, gives access to several protocols via its USB CDC port. Up until now, the neccessary steps to activate these were only partially documented. With **ULFCom**, an overview of the involved procedures is provided to enter and leave the following protocols:
  
  - SUSIV2: gives access to ZUSI soundload
  - DCC_EIN: DCC packet control
  - DECUP_EIN: MX firmware and sound update
  - Binary: A command and control protocol, originally implemented for the MX1 command station
  - MDU_EIN: MS firmware and sound update

 

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