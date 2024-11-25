
const { exec } = require('child_process');
const util = require('util');
const execPromise = util.promisify(exec);

async function addContractor(name, rate, skillset) {
    try {
        const { stdout } = await execPromise(`./backend addContractor "${name}" ${rate} "${skillset}"`);
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function listContractors() {
    try {
        const { stdout } = await execPromise('./backend listContractors');
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function deleteContractor(id) {
    try {
        const { stdout } = await execPromise(`./backend deleteContractor ${id}`);
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function updateContractor(id, name, rate, skillset) {
    try {
        const { stdout } = await execPromise(`./backend updateContractor ${id} "${name}" ${rate} "${skillset}"`);
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function searchContractors(rate, skillset) {
    try {
        const { stdout } = await execPromise(`./backend searchContractors ${rate} "${skillset}"`);
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function addJob(description, requiredSkill, price, urgency) {
    try {
        const { stdout } = await execPromise(`./backend addJob "${description}" "${requiredSkill}" ${price} ${urgency}`);
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function listJobs() {
    try {
        const { stdout } = await execPromise('./backend listJobs');
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function deleteJob(id) {
    try {
        const { stdout } = await execPromise(`./backend deleteJob ${id}`);
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function updateJob(id, field, newValue) {
    try {
        const { stdout } = await execPromise(`./backend updateJob ${id} "${field}" "${newValue}"`);
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function sortContractorsByRate() {
    try {
        const { stdout } = await execPromise('./backend sortContractorsByRate');
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function sortJobsByPrice() {
    try {
        const { stdout } = await execPromise('./backend sortJobsByPrice');
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function prioritizeJobs() {
    try {
        const { stdout } = await execPromise('./backend prioritizeJobs');
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function getMostUrgentJob() {
    try {
        const { stdout } = await execPromise('./backend getMostUrgentJob');
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function searchJobsByPriceRange(minPrice, maxPrice) {
    try {
        const { stdout } = await execPromise(`./backend searchJobsByPriceRange ${minPrice} ${maxPrice}`);
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function matchJobsToContractorRate(contractorRate) {
    try {
        const { stdout } = await execPromise(`./backend matchJobsToContractorRate ${contractorRate}`);
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

async function deleteDB() {
    try {
        const { stdout } = await execPromise('./backend deleteDB');
        return stdout.trim();
    } catch (error) {
        throw new Error(error.stderr.trim());
    }
}

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
