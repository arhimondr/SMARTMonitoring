/**
 * Created with IntelliJ IDEA.
 * User: andy
 * Date: 9/29/13
 * Time: 6:57 PM
 * To change this template use File | Settings | File Templates.
 */

/**
 * @namespace
 */
SMARTMonitoring = {};

/**
 * Identify data holder object
 *
 * @constructor
 */
SMARTMonitoring.IdentifyInfo = function(obj){

    obj = obj || {};

    /**
     * Model of the device
     *
     * @type {string}
     */
    this.model = obj.model || "";

    /**
     * Serial number of a device
     *
     * @type {string}
     * @property
     */
    this.serial = obj.serial || "";


    /**
     * Device firmware code
     *
     * @type {string}
     */
    this.firmware = obj.firmware || "";
};

/**
 * Smart attribute object
 *
 * @constructor
 */
SMARTMonitoring.SmartAttribute = function(obj){

    obj = obj || {};

    /**
     * Attribute ID
     *
     * @type {number}
     */
    this.id = obj.id || 0;

    /**
     * Attribute name
     *
     * @type {string}
     */
    this.name = obj.name || "";

    /**
     * Attribute warning!!
     *
     * @type {boolean}
     */
    this.warn = obj.warn || false;

    /**
     * TODO: ???
     *
     * @type {boolean}
     */
    this.online = obj.online || false;

    /**
     * TODO: ???
     *
     * @type {string}
     */
    this.prefailure = obj.prefailure || "";

    /**
     * Attribute flags
     *
     * @type {number}
     */
    this.flags = obj.flags || 0;

    /**
     * TODO: ???
     *
     * @type {boolean}
     */
    this.threshold_valid = obj.threshold_valid || false;

    /**
     * TODO: ???
     *
     * @type {number}
     */
    this.threshold = obj.threshold || 0;

    /**
     * TODO: ???
     *
     * @type {boolean}
     */
    this.good_now_valid = obj.good_now_valid || false;

    /**
     * TODO: ???
     *
     * @type {boolean}
     */
    this.good_now = obj.good_now || false;

    /**
     * TODO: ???
     *
     * @type {boolean}
     */
    this.good_in_the_past_valid = obj.good_in_the_past_valid || false;

    /**
     * TODO: ???
     *
     * @type {boolean}
     */
    this.good_in_the_past = obj.good_in_the_past || false;

    /**
     * TODO: ???
     *
     * @type {boolean}
     */
    this.current_value_valid = obj.current_value_valid || false;

    /**
     * TODO: ???
     *
     * @type {boolean}
     */
    this.current_value = obj.current_value || false;


    /**
     * TODO: ???
     *
     * @type {boolean}
     */
    this.worst_value_valid = obj.worst_value_valid || false;

    /**
     * TODO: ???
     *
     * @type {boolean}
     */
    this.worst_value = obj.worst_value || false;

    /**
     * TODO: ???
     *
     * @type {number}
     */
    this.pretty_value = obj.pretty_value || 0;


    /**
     * TODO: ???
     *
     * @type {Array}
     */
    this.raw = obj.raw || [0,0,0,0,0,0];
}

/**
 * Smart Info
 *
 * @constructor
 */
SMARTMonitoring.SmartInfo = function(obj){

    obj = obj || {};

    /**
     * Overall disk status boolean. false - bad, true - good
     *
     * @type {boolean}
     */
    this.diskStatus = obj.diskStatus || false;

    /**
     * Overall status string
     *
     * Possible values:
     *
     * "GOOD"
     * "BAD_ATTRIBUTE_IN_THE_PAST",
     * "BAD_SECTOR",
     * "BAD_ATTRIBUTE_NOW",
     * "BAD_SECTOR_MANY",
     * "BAD_STATUS"
     *
     * @type {string}
     */
    this.overall = obj.overall || "";

    /**
     * Number of bad sectors on disk
     *
     * @type {number}
     */
    this.badSectors = obj.badSectors || 0;

    /**
     * Powered on time msecs
     *
     * @type {number}
     */
    this.poweredOnMsecs = obj.poweredOnMsecs || 0;

    /**
     * Number of HDD power cycles
     *
     * @type {number}
     */
    this.powerCycles = obj.powerCycles || 0;

    /**
     * Disk temperature
     *
     * @type {number}
     */
    this.temperatureK = obj.temperatureK || 0;

    /**
     * Attributes verification
     *
     * Possible values:
     *
     * Bad - means that TODO
     * Good - all things is good TODO
     *
     * @type {string}
     */
    this.attributeVerification = obj.attributeVerification || "";

    /**
     *
     * @type {SMARTMonitoring.SmartAttribute[]}
     */
    this.attributes = [];

    if(obj.attributes && obj.attributes.length){
        for(var i=0; i<obj.attributes.length; i++){
            this.attributes.push(new SMARTMonitoring.SmartAttribute(obj.attributes[i]));
        }
    }
}

/**
 * @constructor
 */
SMARTMonitoring.DiskInfo = function(obj){

    obj = obj || {};


    /**
     * Device mount point on server
     *
     * @type {string}
     */
    this.devicePath = obj.devicePath || "";

    /**
     * Is S.M.A.R.T data available for given device
     *
     * @type {boolean}
     */
    this.smartAvailable = obj.smartAvailable || false;


    /**
     * Is Identify data available for given device
     *
     * @type {boolean}
     */
    this.identifyValid = obj.identifyValid || false;

    /**
     * Name of device
     *
     * @type {string}
     */
    this.name = obj.name || "";

    /**
     * Device Type
     *
     * @type {string}
     */
    this.type = obj.type || "";


    /**
     * Device Type pretty print
     *
     * @type {string}
     */
    this.typePretty = obj.typePretty || "";

    /**
     * Device full size in bytes
     *
     * @type {number}
     */
    this.size = obj.size || 0;

    /**
     * Identify info for device. Could be null when identifyValid = false
     *
     * @type {SMARTMonitoring.Identify}
     */
    this.identifyInfo = new SMARTMonitoring.IdentifyInfo(obj.identifyInfo);

    /**
     * S.M.A.R.T. info for drive. Could be null when smartAvailable = false
     *
     * @type {SMARTMonitoring.SmartInfo}
     */
    this.smartInfo = new SMARTMonitoring.SmartInfo(obj.smartInfo);
}

/**
 * Info about all hdds from the server
 *
 * @constructor
 */
SMARTMonitoring.Disks = function(obj){

    obj = obj || {};

    /**
     * Some drives found??
     *
     * @type {boolean}
     */
    this.found = obj.found || false;


    /**
     *
     * @type {SMARTMonitoring.DiskInfo[]}
     */
    this.disks = [];

    if(this.found && obj.disks && obj.disks.length){

        for(var i=0; i<obj.disks.length; i++){
            this.disks.push(new SMARTMonitoring.DiskInfo(obj.disks[i]));
        }

    }


}
