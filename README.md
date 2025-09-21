# lite-rundll - Easyfull and light rundll32.exe (but 64-bit :d)


```diff
Pros/Minuses:

+ lighter
+ simplicity
+ written in pure C

- no support of arguments
```

### Proof of light size
<img width="1092" height="540" alt="Untitled" src="https://github.com/user-attachments/assets/be8cef18-df21-415c-9a58-99b88d4ee7d8" />


### q/a

q: Can this replace the system's rundll32.exe?\
a: It won't be able to until I add support for arguments.

### usage
`lite-rundll.exe {TYPE} {DLLFile} [ENTRYPOINT]`

**Types:**  
1.  **Loads the DLL file and executes the standard entry point: `DLLMain`**
2.  **Loads the DLL file and executes a custom entry point (the third argument)**  
3.  **Loads the DLL file and executes a custom entry point (the third argument) (Imports - forbidden)**

**P.S.** The 2nd method of execution: if the DLL file contains a `DLLMain`, it will execute it first, before the custom entry point. If the DLL file has a `DLLMain` but you need to call another part without triggering `DLLMain`, use the 3rd method.

> **Note:** In the 3rd method, imports are forbidden and the export table is not populated, which may lead to unexpected behavior.
