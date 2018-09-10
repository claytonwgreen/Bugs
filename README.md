# Bugs

### Dependencies 
* [XQuartz](https://www.xquartz.org/releases/index.html)
	* Built using v 2.7.11 

---

### Running
```bash
./[Executable] [FieldFile] [BugFile] [BugFile] [BugFile] [BugFile]
```
- Executable:
	* The binary executable made from building this repo ("Bugs" in this repo) 	
- FieldFile:
	* The file used to create the playing field (provided in "FieldFiles" folder)
- BugFile:
	* File that each player creates with the logic for their ant colony
	* 2-4 of these required 
 
Ex:
```bash
./Bugs ./FieldFiles/fieldFileMain.txt ./Ants/dumbant1.bug.txt ./Ants/dumbant2.bug.txt ./Ants/smartant.bug.txt ./Ants/smartant2.bug.txt -raw
```

---