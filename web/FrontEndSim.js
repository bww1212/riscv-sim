class FrontEndSim {
    uploadFile() {
        fileExtension = fileupload.split('.').pop();
        if (fileExtension != 'o') {
            window.alert("Please enter an object file.");
        }
        
        // Parse the file
    }
}