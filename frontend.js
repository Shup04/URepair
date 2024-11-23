const { exec } = require('child_process');

// Function to add a user
function addUser(name, email) {
    // error stdout and stderr are the outputs from the cpp backend
    exec(`./backend addUser "${name}" "${email}"`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Lists users
function listUsers() {
    exec('./backend listUsers', (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout); 
        }
    });
}

// Example usage
//addUser("John Doe", "john@example.com");
listUsers();
