const { exec } = require('child_process');

// Adds a new contractor
function addContractor(name, rate, skillset) {
    exec(`./backend addContractor "${name}" ${rate} "${skillset}"`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Lists all contractors
function listContractors() {
    exec('./backend listContractors', (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Deletes a contractor
function deleteContractor(id) {
    exec(`./backend deleteContractor ${id}`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Updates a contractor
function updateContractor(id, name, rate, skillset) {
    exec(`./backend updateContractor ${id} "${name}" ${rate} "${skillset}"`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Searches contractors by rate and skillset
function searchContractors(rate, skillset) {
    exec(`./backend searchContractors ${rate} "${skillset}"`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Adds a new job
function addJob(description, requiredSkill, price, urgency) {
    exec(`./backend addJob "${description}" "${requiredSkill}" ${price} ${urgency}`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Lists all jobs
function listJobs() {
    exec('./backend listJobs', (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Deletes a job
function deleteJob(id) {
    exec(`./backend deleteJob ${id}`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Updates a job
function updateJob(id, field, newValue) {
    exec(`./backend updateJob ${id} "${field}" "${newValue}"`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Sorts contractors by rate
function sortContractorsByRate() {
    exec('./backend sortContractorsByRate', (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Sorts jobs by price
function sortJobsByPrice() {
    exec('./backend sortJobsByPrice', (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Prioritizes jobs by urgency
function prioritizeJobs() {
    exec('./backend prioritizeJobs', (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Gets the most urgent job
function getMostUrgentJob() {
    exec('./backend getMostUrgentJob', (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Searches jobs by price range
function searchJobsByPriceRange(minPrice, maxPrice) {
    exec(`./backend searchJobsByPriceRange ${minPrice} ${maxPrice}`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Matches jobs to contractor rate
function matchJobsToContractorRate(contractorRate) {
    exec(`./backend matchJobsToContractorRate ${contractorRate}`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Deletes the database
function deleteDB() {
    exec('./backend deleteDB', (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${stderr}`);
        } else {
            console.log(stdout);
        }
    });
}

// Exports for Node.js
module.exports = {
    addContractor,
    listContractors,
    deleteContractor,
    updateContractor,
    searchContractors,
    addJob,
    listJobs,
    deleteJob,
    updateJob,
    sortContractorsByRate,
    sortJobsByPrice,
    prioritizeJobs,
    getMostUrgentJob,
    searchJobsByPriceRange,
    matchJobsToContractorRate,
    deleteDB,
};
