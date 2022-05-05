"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (_) try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [op[0] & 2, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
exports.__esModule = true;
var admin = require("firebase-admin");
var functions = require("firebase-functions");
var jws_1 = require("jws");
var axios_1 = require("axios");
/** Public webapp key. Required by `signInWithCustomToken` REST API.  */
var WEBAPP_APIKEY = "AIzaSyBP44Gfd6kGU6ieVAuUaRGcpvESm4bh55Q";
/** Looks up and returns a device by its id. */
function getDevice(id) {
    return __awaiter(this, void 0, void 0, function () {
        var docSnapshot;
        return __generator(this, function (_a) {
            switch (_a.label) {
                case 0: return [4 /*yield*/, deviceCollection.doc(id).get()];
                case 1:
                    docSnapshot = _a.sent();
                    return [2 /*return*/, docSnapshot.exists
                            ? { id: docSnapshot.id, data: docSnapshot.data() }
                            : null];
            }
        });
    });
}
/** Prints a decoded representation, alongside the JWT to the console. */
function printJWT(message, token) {
    var _a = (0, jws_1.decode)(token), header = _a.header, payload = _a.payload;
    console.log(message, header, payload, token);
}
/** Generates, persists and returns a unique (per device) number. */
function getNextNonce(device) {
    return __awaiter(this, void 0, void 0, function () {
        var nonce;
        return __generator(this, function (_a) {
            switch (_a.label) {
                case 0:
                    nonce = (device.data.nonce || 0) + 1;
                    return [4 /*yield*/, deviceCollection.doc(device.id).update({
                            nonce: nonce,
                            getIdTokenTime: admin.firestore.FieldValue.serverTimestamp()
                        })];
                case 1:
                    _a.sent();
                    return [2 /*return*/, nonce];
            }
        });
    });
}
/**
 * Reformats the base64 encoded key.
 * When manually copying the key, some whitespace is changed, making the key non-compliant with the spec.
 */
function normalizePublicKey(pk) {
    return ("-----BEGIN PUBLIC KEY-----\n" +
        pk.replace(/\\s|-----(BEGIN|END) PUBLIC KEY-----/g, "") +
        "\n-----END PUBLIC KEY-----\n");
}
admin.initializeApp();
var deviceCollection = admin
    .firestore()
    .collection("devices");
/** Generates and returns new Firebase id token for the provided device token. */
exports.getIdToken = functions.https.onRequest(function (req, res) { return __awaiter(void 0, void 0, void 0, function () {
    var deviceToken, _a, header, payload, device, _b, alg, verifyResult, payloadNonce, nonce, _c, customToken, idTokenResponse, idToken, _d, _e;
    var _f;
    return __generator(this, function (_g) {
        switch (_g.label) {
            case 0:
                deviceToken = req.body;
                printJWT("Device token: ", deviceToken);
                _a = (0, jws_1.decode)(deviceToken), header = _a.header, payload = _a.payload;
                _b = header.kid;
                if (!_b) return [3 /*break*/, 2];
                return [4 /*yield*/, getDevice(header.kid)];
            case 1:
                _b = (_g.sent());
                _g.label = 2;
            case 2:
                device = _b;
                if (!device) {
                    res.status(401).send({
                        errorCode: 1,
                        message: "Unknown device!"
                    });
                    return [2 /*return*/];
                }
                console.log("Device found: ", device.id, device.data);
                alg = "ES256";
                verifyResult = (0, jws_1.verify)(deviceToken, alg, normalizePublicKey(device.data.publicKey));
                if (!verifyResult || header.alg !== alg) {
                    res.status(401).send({
                        errorCode: 4,
                        message: "Invalid JWT!"
                    });
                    return [2 /*return*/];
                }
                payloadNonce = Number(JSON.parse(payload).nonce);
                _c = device.data.nonce;
                if (_c) return [3 /*break*/, 4];
                return [4 /*yield*/, getNextNonce(device)];
            case 3:
                _c = (_g.sent());
                _g.label = 4;
            case 4:
                nonce = _c;
                if (payloadNonce !== nonce) {
                    // Invalid nonce.
                    // Not necessarily a replay attack, the device might just be out of sync due to a network error.
                    res.status(401).send({
                        errorCode: 3,
                        message: "Invalid nonce!",
                        nonce: nonce
                    });
                    return [2 /*return*/];
                }
                if (!device.data.uid) {
                    // This device is not associated with a user account.
                    res.status(401).send({
                        errorCode: 2,
                        message: "Unclaimed device!"
                    });
                    return [2 /*return*/];
                }
                return [4 /*yield*/, admin
                        .auth()
                        .createCustomToken(device.data.uid, { deviceId: device.id })];
            case 5:
                customToken = _g.sent();
                printJWT("Custom token: ", customToken);
                return [4 /*yield*/, axios_1["default"].post("https://identitytoolkit.googleapis.com/v1/accounts:signInWithCustomToken?key=" +
                        WEBAPP_APIKEY, { token: customToken, returnSecureToken: true })];
            case 6:
                idTokenResponse = _g.sent();
                idToken = idTokenResponse.data.idToken;
                printJWT("Id token: ", idToken);
                _e = (_d = res).send;
                _f = {};
                return [4 /*yield*/, getNextNonce(device)];
            case 7:
                _e.apply(_d, [(_f.nonce = _g.sent(),
                        _f.idToken = idToken,
                        _f)]);
                return [2 /*return*/];
        }
    });
}); });
