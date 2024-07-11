import pydantic
from pymongo import MongoClient
from dotenv import load_dotenv
import os
from enum import Enum, auto
import re

load_dotenv(override=True)

CONNECTION_STRING = os.getenv('MONGO_CONN_STR')
URL_REGEX = r"https:\/\/github.com\/[a-zA-Z0-9_-]+(\/[a-zA-Z0-9_-]+)+"

class TLDs(Enum):
    TURTLE = auto()
    SEATURTLE = auto()
    SHELL = auto()
    OCEAN = auto()
    MARINE = auto()
    WAVES = auto()
    REEF = auto()
    CORAL = auto()
    SEA = auto()
    BLUE = auto()


class SiteModel(pydantic.BaseModel):
    domain: str
    tld: str
    github: str

    @pydantic.field_validator('github')
    @classmethod
    def validate_github(cls, github):
        if not re.match(URL_REGEX, github):
            raise ValueError("Invalid URL passed in for github link")
        return github

    @pydantic.field_validator('tld')
    @classmethod
    def validate_tld(cls, tld):
        if not (tld.upper() in TLDs._member_map_ and tld.islower()):
            raise ValueError("Given TLD does not match specified pattern.")
        return tld

def register_site(domain: str, tld: str, github: str):
    site_data = SiteModel(domain=domain, tld=tld, github=github)

    client = MongoClient(CONNECTION_STRING)
    client['sites']['all'].insert_one(dict(site_data))

    return 0

def main(): print("hello, world!")