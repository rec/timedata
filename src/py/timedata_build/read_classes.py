from . import class_descriptions, template
from . context import Context


MODELS = (
    ('RGB', ('red', 'green', 'blue')),
    ('HSL', ('hue', 'saturation', 'lightness')),
    ('HSV', ('hue', 'saturation', 'value')),
    ('XYZ', ('x', 'y', 'z')),
    ('YIQ', ('luma', 'inphase', 'quadrature')),
    ('YUV', ('luma', 'uchrominance', 'vchrominance')),
    )


def read_classes(tiny=False, models=[]):
    color_dict = class_descriptions.Color.__dict__
    mutable_dict = class_descriptions.Mutable.__dict__
    color_list_dict = class_descriptions.ColorList.__dict__

    def substitute_context(context, name, **kwds):
        context = dict(context)
        sub = template.substituter(name=name, **kwds)

        for k, v in context.pop('substitutions', {}).items():
            context[k] = sub(v)
        return Context(**context)

    def read_class(model, properties, range_name):
        name = model + range_name
        color_name = 'Color' + name
        mutable_name = 'Mutable' + color_name

        if models:
            if name.lower() not in models:
                return
        elif tiny:
            if range_name or (model not in ('RGB', 'HSV')):
                return
        else:
            if range_name and model != 'RGB':
                return
        kwds = dict(
            range=range_name or '1',
            mutableclass=mutable_name,
            sampleclass=color_name)

        def sub(cl, name, **props):
            return substitute_context(dict(cl, **props), name, **kwds)

        yield sub(color_dict, color_name, properties=properties)
        yield sub(mutable_dict,
                  mutable_name,
                  mutable_properties=properties,
                  parentclass=color_name)
        yield sub(color_list_dict, 'ColorList' + name)

    for model, prop in MODELS:
        for range_name in '', '255', '256':
            yield from read_class(model, prop, range_name)
