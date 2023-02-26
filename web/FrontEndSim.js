var byteArrayFromObject;
var instructionCounter;
var delayTime = 10;

function uploadFile() {
    fileExtension = document.getElementById("fileUpload").value.split('.').pop();
    if (fileExtension != 'png') {
        window.alert("Please enter an object file.");
        return null;
    }
}

function parseFile(file) {
    return new Promise((resolve, reject) => {
        try {
            var reader = new FileReader();
            let byteArray = [];
            reader.readAsArrayBuffer(file);
            reader.onloadend = (evt) => {
                if (evt.target.readyState == FileReader.DONE) {
                    let buffer = evt.target.result,
                    array = new Uint8Array(buffer);
                    for (byte of array) {
                        byteArray.push(byte);
                    }
                }
                resolve(byteArray);
            }
        }
        catch (e) {
            reject(e);
        }
    })
}

function printRegisters() {
    result = Module.ccall('getRegisters')
    for (i = 0; i < 32; i++) {
        // Print register i in a 4x8 grid
    }
    console.log(result);
    document.getElementById('registers').value = result;
}

function printInstructions() {
    // Print the instruction list
    // Call with an offset
    // If calling with 0, that will give the instruction being called, 1 will be the one after that and so on
    result = Module.ccall('getInstructionStream', '0');
    console.log(result);
    document.getElementById('instructions').value = result;
}

function printMemoryView() {
    // Print view of memory in a scroll box
    result = Module.ccall('getMemory')
    console.log(result);
    document.getElementById('memory').value = result;
}

function setMemorySize(sizeInBytes) {
    sizeInBytes = toString(sizeInBytes);
    Module.ccall('setMemorySize', sizeInBytes);
}

function executeOneInstruction() {
    // Call method to run one instruction
    Module.cwrap('getInstructionStream', '0');
}

function executeTenInstructions() {
    for (i = 0; i < 10; i++) {
        this.executeOneInstruction()
    }
}

function delay(milliseconds) {
    return new Promise(resolve => {
        setTimeout(() => {resolve('')}, milliseconds);
    })
}

async function playInstructions() {
    value = true;
    while (value) {
        console.log(this.executeOneInstruction());
        await delay(delayTime);
        console.log(delayTime);
    }
}

function stopInstructions() {
    value = false;
}

function changeDelay() {
    delayTime = parseInt(document.getElementById("delayInput").value);
}

function initSim() {
    Module.onRuntimeInitialized = () => {
        setMemorySize(4000);
        printInstructions();
        printMemoryView();
        printRegisters();
    };
}