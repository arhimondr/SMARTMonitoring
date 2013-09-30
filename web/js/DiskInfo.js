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
 * Plain compare to
 *
 * @param {Object} obj
 * @return {number}
 */
Object.prototype.compareTo = function(obj){
    return this<obj ? -1 : (this>obj ? 1 : 0);
}

/**
 * Compare strings
 *
 * @param {String} obj
 * @return {number}
 */
String.prototype.compareTo = function(obj){
    return this<obj ? -1 : (this>obj ? 1 : 0);
}

/**
 * Sort array of object by compareTo method
 */
Array.prototype.sortObjects = function(){
    this.sort(function(a, b){
        return a.compareTo(b);
    })
}

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
 * Overall priority
 */
SMARTMonitoring.SmartInfo.OVERALL_PRIORITY = {
    "GOOD" : 0,
    "BAD_ATTRIBUTE_IN_THE_PAST" : 2,
    "BAD_SECTOR" : 3,
    "BAD_ATTRIBUTE_NOW" : 4,
    "BAD_SECTOR_MANY" : 5,
    "BAD_STATUS" : 6
}

/**
 * Compare function
 *
 * @param {SMARTMonitoring.SmartInfo} obj
 */
SMARTMonitoring.SmartInfo.prototype.compareTo = function(obj){

    if(obj.constructor !== SMARTMonitoring.SmartInfo){
        throw "Unexpected object inside compare to";
    }

    if(this.diskStatus<obj.diskStatus){

        return -1;

    } else if(this.diskStatus>obj.diskStatus){

        return 1;

    } else {

        var OVERALL_PRIORITY = SMARTMonitoring.SmartInfo.OVERALL_PRIORITY;

        if(OVERALL_PRIORITY[this.overall]<OVERALL_PRIORITY[obj.overall]){

            return 1;

        } else if(OVERALL_PRIORITY[this.overall]>OVERALL_PRIORITY[obj.overall]){

            return -1;

        } else {

            return this.attributeVerification.compareTo(obj.attributeVerification);

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
 * Compare function
 *
 * @param {SMARTMonitoring.DiskInfo} obj
 */
SMARTMonitoring.DiskInfo.prototype.compareTo = function(obj){
    if(obj.constructor !== SMARTMonitoring.DiskInfo){
        throw "Unexpected object inside compare to";
    }

    if(this.smartAvailable && !obj.smartAvailable){

        return -1;

    } else if(!this.smartAvailable && obj.smartAvailable){

        return 1;

    } else if(!this.smartAvailable && !obj.smartAvailable){

        return this.devicePath.compareTo(obj.devicePath)

    } else {

        var smartCompareResult = this.smartInfo.compareTo(obj.smartInfo);

        if(smartCompareResult==0){
            return this.devicePath.compareTo(obj.devicePath);
        }

    }
}

/**
 * Info about all hdds from the server
 *
 * @constructor
 */
SMARTMonitoring.ServerInfo = function(obj){

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

    /**
     *
     * For example
     *
     * 0 - no bad drives on server
     *
     * 100 - a lot of bad drives
     *
     * @type {number}
     */
    this.totalOverAllIndex = 0;

    var OVERALL_PRIORITY = SMARTMonitoring.SmartInfo.OVERALL_PRIORITY;

    if(this.found && obj.disks && obj.disks.length){

        for(var i=0; i<obj.disks.length; i++){

            /**
             * Current disk
             *
             * @type {SMARTMonitoring.DiskInfo}
             */
            var disk = new SMARTMonitoring.DiskInfo(obj.disks[i]);

            if(disk.smartAvailable){
                this.totalOverAllIndex+=OVERALL_PRIORITY[disk.smartInfo.overall];
            }


            this.disks.push(disk);
        }

    }

    this.disks.sortObjects();


}

/**
 * Compare 2 server priority
 *
 *
 * @param {SMARTMonitoring.ServerInfo} obj
 */
SMARTMonitoring.ServerInfo.prototype.compareTo = function(obj){
    return this.totalOverAllIndex > obj.totalOverAllIndex ? -1
        : (this.totalOverAllIndex < obj.totalOverAllIndex ? 1 : 0);
}
